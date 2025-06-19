/*
* Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
* Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License").
* You may not use this file except in compliance with the License.
* A copy of the License is located at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
* or in the "license" file accompanying this file. This file is distributed
* on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied. See the License for the specific language governing
* permissions and limitations under the License.
*/

#include "../Public/Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

#include "Core/Domain/Gs2.h"
#include "Distributor/Gs2DistributorRestClient.h"

namespace Gs2::Core::Domain
{
	FTransactionAccessTokenDomainPtr FManualTransactionAccessTokenDomain::HandleResult(
		const FString Action,
		const TSharedPtr<FJsonObject>& ResultJson
	)
	{
		if (ResultJson.IsValid()) {
			auto NextTransactions = MakeShared<TArray<FTransactionAccessTokenDomainPtr>>();
			if (Action == "Gs2JobQueue:PushByUserId")
			{
				NextTransactions->Add(NewJobQueueDomain(
					Gs2::JobQueue::Result::FPushByUserIdResult::FromJson(ResultJson)
				));
			}

			if (ResultJson->HasField(ANSI_TO_TCHAR("autoRunStampSheet"))) {
				NextTransactions->Add(NewTransactionDomain(
					ResultJson->HasField(ANSI_TO_TCHAR("autoRunStampSheet")) && ResultJson->GetBoolField(ANSI_TO_TCHAR("autoRunStampSheet")),
					ResultJson->HasField(ANSI_TO_TCHAR("transactionId")) ? ResultJson->GetStringField(ANSI_TO_TCHAR("transactionId")) : FString(""),
                    ResultJson->HasField(ANSI_TO_TCHAR("stampSheet")) ? ResultJson->GetStringField(ANSI_TO_TCHAR("stampSheet")) : FString(""),
                    ResultJson->HasField(ANSI_TO_TCHAR("stampSheetEncryptionKeyId")) ? ResultJson->GetStringField(ANSI_TO_TCHAR("stampSheetEncryptionKeyId")) : FString(""),
                    ResultJson->HasField(ANSI_TO_TCHAR("atomicCommit")) && ResultJson->GetBoolField(ANSI_TO_TCHAR("atomicCommit")),
                    ResultJson->HasField(ANSI_TO_TCHAR("transactionResult")) ? Gs2::Core::Model::FTransactionResult::FromJson(ResultJson->GetObjectField(ANSI_TO_TCHAR("transactionResult"))) : nullptr
				));
			}
			if (NextTransactions->Num() > 0) {
				return MakeShared<FTransactionAccessTokenDomain>(
					Gs2,
					NewJobQueueDomain,
					NewTransactionDomain,
					AccessToken,
					NextTransactions
				);
			}
		}
		return nullptr;
	}

	FManualTransactionAccessTokenDomain::FManualTransactionAccessTokenDomain(
		const FGs2Ptr& Gs2,
		const TFunction<TSharedPtr<FTransactionAccessTokenDomain>(
			const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
		)>& NewJobQueueDomain,
		const TFunction<TSharedPtr<FTransactionAccessTokenDomain>(
			bool bAutoRun,
			FString TransactionId,
			FString StampSheet,
			FString StampSheetEncryptionKeyId,
			bool bAtomicCommit,
			Gs2::Core::Model::FTransactionResultPtr TransactionResult
		)>& NewTransactionDomain,
		const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
		const FString TransactionId,
		const FString StampSheet,
		const FString StampSheetEncryptionKeyId
	):
		FTransactionAccessTokenDomain(
			Gs2,
			NewJobQueueDomain,
			NewTransactionDomain,
			AccessToken,
			nullptr
		),
		TransactionId(TransactionId),
		StampSheet(StampSheet),
		StampSheetEncryptionKeyId(StampSheetEncryptionKeyId)
	{
	        
	}

	FManualTransactionAccessTokenDomain::FManualTransactionAccessTokenDomain(
		const FManualTransactionAccessTokenDomain& From
	):
		FTransactionAccessTokenDomain(
			From.Gs2,
			From.NewJobQueueDomain,
			From.NewTransactionDomain,
			From.AccessToken,
			nullptr
		),
		TransactionId(From.TransactionId),
		StampSheet(From.StampSheet),
		StampSheetEncryptionKeyId(From.StampSheetEncryptionKeyId)
	{
	}

	Gs2::Core::Model::FGs2ErrorPtr FManualTransactionAccessTokenDomain::WaitImpl(
		const bool All,
		TSharedPtr<TSharedPtr<FTransactionAccessTokenDomain>> Result
	)
	{
        auto Client = MakeShared<Gs2::Distributor::FGs2DistributorRestClient>(
            Gs2->RestSession
        );
		TSharedPtr<FJsonObject> StampSheetJson;
		if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(StampSheet);
			!FJsonSerializer::Deserialize(JsonReader, StampSheetJson))
		{
			return nullptr;
		}
		auto StampSheetPayload = StampSheetJson->GetStringField(ANSI_TO_TCHAR("body"));
		TSharedPtr<FJsonObject> StampSheetPayloadJson;
		if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(StampSheetPayload);
			!FJsonSerializer::Deserialize(JsonReader, StampSheetPayloadJson))
		{
			return nullptr;
		}
        auto VerifyTasks = StampSheetPayloadJson->GetArrayField(ANSI_TO_TCHAR("verifyTasks"));
        auto StampTasks = StampSheetPayloadJson->GetArrayField(ANSI_TO_TCHAR("tasks"));
        TOptional<FString> contextStack;
        for (auto i = 0; i < VerifyTasks.Num(); i++)
        {
        	auto VerifyTask = VerifyTasks[i]->AsString();
        	TSharedPtr<FJsonObject> stampTaskJson;
        	if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(VerifyTask);
				!FJsonSerializer::Deserialize(JsonReader, stampTaskJson))
        	{
        		return nullptr;
        	}
        	auto VerifyTaskPayload = stampTaskJson->GetStringField(ANSI_TO_TCHAR("body"));
        	TSharedPtr<FJsonObject> stampTaskPayloadJson;
        	if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(VerifyTaskPayload);
				!FJsonSerializer::Deserialize(JsonReader, stampTaskPayloadJson))
        	{
        		return nullptr;
        	}
            if (!Gs2->TransactionConfiguration.IsValid() || !Gs2->TransactionConfiguration->NamespaceName.IsSet() || Gs2->TransactionConfiguration->NamespaceName->IsEmpty())
            {
                auto Future = Client->RunVerifyTaskWithoutNamespace(
                    MakeShared<Gs2::Distributor::Request::FRunVerifyTaskWithoutNamespaceRequest>()
                            ->WithContextStack(contextStack)
                            ->WithVerifyTask(VerifyTasks[i]->AsString())
                            ->WithKeyId(StampSheetEncryptionKeyId)
                            );
            	Future->StartSynchronousTask();
            	if (Future->GetTask().IsError())
            	{
            		return Future->GetTask().Error();
            	}
            	const auto FutureResult = Future->GetTask().Result();
                contextStack = FutureResult->GetContextStack();
            }
            else
            {
                auto Future = Client->RunVerifyTask(
                    MakeShared<Gs2::Distributor::Request::FRunVerifyTaskRequest>()
                        ->WithContextStack(contextStack)
                        ->WithNamespaceName(Gs2->TransactionConfiguration->NamespaceName)
                        ->WithVerifyTask(VerifyTasks[i]->AsString())
                        ->WithKeyId(StampSheetEncryptionKeyId)
                        );
            	Future->StartSynchronousTask();
            	if (Future->GetTask().IsError())
            	{
                    if (Future->GetTask().Error()->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
                    {
                    	if (Gs2->TransactionConfiguration.IsValid()) {
                    		Gs2->TransactionConfiguration->NamespaceName = TOptional<FString>();
                    		auto Future2 = Wait(All);
                    		Future2->StartSynchronousTask();
                    		if (Future2->GetTask().IsError())
                    		{
                    			return Future2->GetTask().Error();
                    		}
                    		*Result = Future2->GetTask().Result();
                    		return nullptr;
                    	}
                    }
            		return Future->GetTask().Error();
            	}
                auto FutureResult = Future->GetTask().Result();
                contextStack = FutureResult->GetContextStack();
            }
        }
        for (auto i = 0; i < StampTasks.Num(); i++)
        {
        	auto StampTask = StampTasks[i]->AsString();
        	TSharedPtr<FJsonObject> stampTaskJson;
        	if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(StampTask);
				!FJsonSerializer::Deserialize(JsonReader, stampTaskJson))
        	{
        		return nullptr;
        	}
        	auto StampTaskPayload = stampTaskJson->GetStringField(ANSI_TO_TCHAR("body"));
        	TSharedPtr<FJsonObject> stampTaskPayloadJson;
        	if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(StampTaskPayload);
				!FJsonSerializer::Deserialize(JsonReader, stampTaskPayloadJson))
        	{
        		return nullptr;
        	}
            if (!Gs2->TransactionConfiguration.IsValid() || !Gs2->TransactionConfiguration->NamespaceName.IsSet() || Gs2->TransactionConfiguration->NamespaceName->IsEmpty())
            {
                auto Future = Client->RunStampTaskWithoutNamespace(
                    MakeShared<Gs2::Distributor::Request::FRunStampTaskWithoutNamespaceRequest>()
                            ->WithContextStack(contextStack)
                            ->WithStampTask(StampTasks[i]->AsString())
                            ->WithKeyId(StampSheetEncryptionKeyId)
                            );
            	Future->StartSynchronousTask();
            	if (Future->GetTask().IsError())
            	{
            		return Future->GetTask().Error();
            	}
            	const auto FutureResult = Future->GetTask().Result();
                contextStack = FutureResult->GetContextStack();
                Gs2->TransactionConfiguration->StampTaskEventHandler(
                    stampTaskPayloadJson->GetStringField(ANSI_TO_TCHAR("action")),
                    stampTaskPayloadJson->GetStringField(ANSI_TO_TCHAR("args")),
                    *FutureResult->GetResult()
                );
            }
            else
            {
                auto Future = Client->RunStampTask(
                    MakeShared<Gs2::Distributor::Request::FRunStampTaskRequest>()
                        ->WithContextStack(contextStack)
                        ->WithNamespaceName(Gs2->TransactionConfiguration->NamespaceName)
                        ->WithStampTask(StampTasks[i]->AsString())
                        ->WithKeyId(StampSheetEncryptionKeyId)
                        );
            	Future->StartSynchronousTask();
            	if (Future->GetTask().IsError())
            	{
                    if (Future->GetTask().Error()->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
                    {
                    	if (Gs2->TransactionConfiguration.IsValid()) {
                    		Gs2->TransactionConfiguration->NamespaceName = TOptional<FString>();
                    		auto Future2 = Wait(All);
                    		Future2->StartSynchronousTask();
                    		if (Future2->GetTask().IsError())
                    		{
                    			return Future2->GetTask().Error();
                    		}
                    		*Result = Future2->GetTask().Result();
                    		return nullptr;
                    	}
                    }
            		return Future->GetTask().Error();
            	}
                auto FutureResult = Future->GetTask().Result();
                contextStack = FutureResult->GetContextStack();
                Gs2->TransactionConfiguration->StampTaskEventHandler(
                    stampTaskPayloadJson->GetStringField(ANSI_TO_TCHAR("action")),
                    stampTaskPayloadJson->GetStringField(ANSI_TO_TCHAR("args")),
                    *FutureResult->GetResult()
                );
            }
        }

		TOptional<FString> action;
		TSharedPtr<FJsonObject> resultJson;
		if (!Gs2->TransactionConfiguration.IsValid() || !Gs2->TransactionConfiguration->NamespaceName.IsSet() || Gs2->TransactionConfiguration->NamespaceName->IsEmpty())
        {
            auto Future = Client->RunStampSheetWithoutNamespace(
                MakeShared<Gs2::Distributor::Request::FRunStampSheetWithoutNamespaceRequest>()
                    ->WithContextStack(contextStack)
                    ->WithStampSheet(StampSheet)
                    ->WithKeyId(StampSheetEncryptionKeyId)
                    );
        	Future->StartSynchronousTask();
        	if (Future->GetTask().IsError())
        	{
        		return Future->GetTask().Error();
        	}
        	const auto FutureResult = Future->GetTask().Result();
            Gs2->TransactionConfiguration->StampSheetEventHandler(
                StampSheetPayloadJson->GetStringField(ANSI_TO_TCHAR("action")),
                StampSheetPayloadJson->GetStringField(ANSI_TO_TCHAR("args")),
                *FutureResult->GetResult()
            );
        	action = StampSheetPayloadJson->GetStringField(ANSI_TO_TCHAR("action"));
        	if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(FutureResult->GetResult().IsSet() ? *FutureResult->GetResult() : "{}");
				!FJsonSerializer::Deserialize(JsonReader, resultJson))
        	{
        		return nullptr;
        	}
        }
        else
        {
            auto Future = Client->RunStampSheet(
                MakeShared<Gs2::Distributor::Request::FRunStampSheetRequest>()
                    ->WithContextStack(contextStack)
                    ->WithNamespaceName(Gs2->TransactionConfiguration->NamespaceName)
                    ->WithStampSheet(StampSheet)
                    ->WithKeyId(StampSheetEncryptionKeyId)
                    );
        	Future->StartSynchronousTask();
        	if (Future->GetTask().IsError())
        	{
        		if (Future->GetTask().Error()->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
        		{
        			if (Gs2->TransactionConfiguration.IsValid()) {
        				Gs2->TransactionConfiguration->NamespaceName = TOptional<FString>();
        				auto Future2 = Wait(All);
        				Future2->StartSynchronousTask();
        				if (Future2->GetTask().IsError())
        				{
        					return Future2->GetTask().Error();
        				}
        				*Result = Future2->GetTask().Result();
        				return nullptr;
        			}
        		}
        		return Future->GetTask().Error();
        	}
            auto FutureResult = Future->GetTask().Result();
            Gs2->TransactionConfiguration->StampSheetEventHandler(
                StampSheetPayloadJson->GetStringField(ANSI_TO_TCHAR("action")),
                StampSheetPayloadJson->GetStringField(ANSI_TO_TCHAR("args")),
                *FutureResult->GetResult()
            );
        	action = StampSheetPayloadJson->GetStringField(ANSI_TO_TCHAR("action"));
        	if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(FutureResult->GetResult().IsSet() ? *FutureResult->GetResult() : "{}");
				!FJsonSerializer::Deserialize(JsonReader, resultJson))
        	{
        		return nullptr;
        	}
        }

        auto Transaction = HandleResult(*action, resultJson);
        if (All && Transaction.IsValid()) {
        	auto Future = Transaction->Wait(true);
        	Future->StartSynchronousTask();
        	if (Future->GetTask().IsError())
        	{
        		return Future->GetTask().Error();
        	}
        	*Result = nullptr;
			return nullptr;
        }
        *Result = Transaction;
		return nullptr;
	}

	TSharedPtr<FAsyncTask<FTransactionAccessTokenDomain::FWaitTask>> FManualTransactionAccessTokenDomain::Wait(
		bool All
	)
	{
		return Gs2::Core::Util::New<FAsyncTask<FWaitTask>>(this->AsShared(), [this, All](
			TSharedPtr<TSharedPtr<FTransactionAccessTokenDomain>> Result
		) {
			return WaitImpl(All, Result);
		});
	}
}
