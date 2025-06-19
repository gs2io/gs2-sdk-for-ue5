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

#include "../Public/Core/Domain/Transaction/ManualJobQueueAccessTokenDomain.h"

#include "Core/Domain/Gs2.h"
#include "JobQueue/Domain/Gs2JobQueue.h"
#include "JobQueue/Request/RunRequest.h"

namespace Gs2::Core::Domain
{
	TMap<FString, FDateTime> FManualJobQueueAccessTokenDomain::Handled;
	
	FTransactionAccessTokenDomainPtr FManualJobQueueAccessTokenDomain::HandleResult(
		const Gs2::JobQueue::Model::FJobPtr& Job,
		const Gs2::JobQueue::Model::FJobResultBodyPtr& Result
	)
	{
		auto bSkipCallback = false;
		if (Handled.Contains(JobName)) {
			// TODO: expire handled
		}
		else {
			Handled.Add(JobName, FDateTime::Now() + FTimespan::FromMinutes(3));
		}
            
		if (!bSkipCallback) {
			Gs2->JobQueueDomain->JobQueueExecutedEventHandler(
				Job,
				Result
			);
		}
            
		TSharedPtr<FJsonObject> ResultModelJson;
		if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
			!FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
		{
			return nullptr;
		}
		auto NextTransactions = MakeShared<TArray<FTransactionAccessTokenDomainPtr>>();
		if (Job->GetScriptId()->EndsWith("push_by_user_id")) {
			NextTransactions->Add(NewJobQueueDomain(
				Gs2::JobQueue::Result::FPushByUserIdResult::FromJson(ResultModelJson)
			));
		}
            
		if (ResultModelJson->HasField(ANSI_TO_TCHAR("autoRunStampSheet"))) {
			NextTransactions->Add(NewTransactionDomain(
				ResultModelJson->HasField(ANSI_TO_TCHAR("autoRunStampSheet")) && ResultModelJson->GetBoolField(ANSI_TO_TCHAR("autoRunStampSheet")),
				ResultModelJson->HasField(ANSI_TO_TCHAR("transactionId")) ? ResultModelJson->GetStringField(ANSI_TO_TCHAR("transactionId")) : FString(""),
				ResultModelJson->HasField(ANSI_TO_TCHAR("stampSheet")) ? ResultModelJson->GetStringField(ANSI_TO_TCHAR("stampSheet")) : FString(""),
				ResultModelJson->HasField(ANSI_TO_TCHAR("stampSheetEncryptionKeyId")) ? ResultModelJson->GetStringField(ANSI_TO_TCHAR("stampSheetEncryptionKeyId")) : FString(""),
				ResultModelJson->HasField(ANSI_TO_TCHAR("atomicCommit")) && ResultModelJson->GetBoolField(ANSI_TO_TCHAR("atomicCommit")),
				ResultModelJson->HasField(ANSI_TO_TCHAR("transactionResult")) ? Gs2::Core::Model::FTransactionResult::FromJson(ResultModelJson->GetObjectField(ANSI_TO_TCHAR("transactionResult"))) : nullptr
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

		return nullptr;
	}

	FManualJobQueueAccessTokenDomain::FManualJobQueueAccessTokenDomain(
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
		const FString NamespaceName,
		const FString JobName
	):
		FTransactionAccessTokenDomain(
			Gs2,
			NewJobQueueDomain,
			NewTransactionDomain,
			AccessToken,
			nullptr
		),
		NamespaceName(NamespaceName),
		JobName(JobName)
	{
            
	}

	FManualJobQueueAccessTokenDomain::FManualJobQueueAccessTokenDomain(
		const FManualJobQueueAccessTokenDomain& From
	):
		FTransactionAccessTokenDomain(
			From.Gs2,
			From.NewJobQueueDomain,
			From.NewTransactionDomain,
			From.AccessToken,
			nullptr
		),
		NamespaceName(From.NamespaceName),
		JobName(From.JobName)
	{
	}

	Gs2::Core::Model::FGs2ErrorPtr FManualJobQueueAccessTokenDomain::WaitImpl(
		const bool All,
		TSharedPtr<TSharedPtr<FTransactionAccessTokenDomain>> Result
	)
	{
		RETRY:
		const auto Future = Gs2->JobQueue->Namespace(
			NamespaceName
		)->AccessToken(
			AccessToken
		)->Run(
			MakeShared<Gs2::JobQueue::Request::FRunRequest>()
		);
		Future->StartSynchronousTask();
		if (Future->GetTask().IsError())
		{
			return Future->GetTask().Error();
		}
		const auto FutureResult = Future->GetTask().Result();
		if (FutureResult.IsValid() && FutureResult->GetIsLastJob().GetValue()) {
			return nullptr;
		}
		const auto Future2 = FutureResult->Model();
		Future2->StartSynchronousTask();
		if (Future2->GetTask().IsError())
		{
			return Future2->GetTask().Error();
		}
		auto Job = Future2->GetTask().Result();
		if (!Job.IsValid()) {
			return nullptr;
		}
		if (Job->GetName() != JobName) {
			HandleResult(Job, FutureResult->GetResult());
			goto RETRY;
		}

		const auto Transaction = HandleResult(Job, FutureResult->GetResult());
		if (All && Transaction.IsValid()) {
			const auto Future3 = Transaction->Wait(true);
			Future3->StartSynchronousTask();
			if (Future3->GetTask().IsError())
			{
				return Future3->GetTask().Error();
			}
			*Result = nullptr;
			return nullptr;
		}
		*Result = Transaction;
		return nullptr;
	}

	TSharedPtr<FAsyncTask<FTransactionAccessTokenDomain::FWaitTask>> FManualJobQueueAccessTokenDomain::Wait(bool All)
	{
		return Gs2::Core::Util::New<FAsyncTask<FWaitTask>>(this->AsShared(), [this, All](
			TSharedPtr<TSharedPtr<FTransactionAccessTokenDomain>> Result
		) {
			return WaitImpl(All, Result);
		});
	}
}
