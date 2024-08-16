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

#include "../Public/Core/Domain/Transaction/AutoJobQueueDomain.h"

#include "Core/Domain/Gs2.h"
#include "JobQueue/Domain/Gs2JobQueue.h"

namespace Gs2::Core::Domain
{
	TMap<FString, FDateTime> FAutoJobQueueDomain::Handled;
	
	FTransactionDomainPtr FAutoJobQueueDomain::HandleResult(
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
		auto NextTransactions = MakeShared<TArray<FTransactionDomainPtr>>();
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
				ResultModelJson->HasField(ANSI_TO_TCHAR("stampSheetEncryptionKeyId")) ? ResultModelJson->GetStringField(ANSI_TO_TCHAR("stampSheetEncryptionKeyId")) : FString("")
			));
		}

		if (NextTransactions->Num() > 0) {
			return MakeShared<FTransactionDomain>(
				Gs2,
				NewJobQueueDomain,
				NewTransactionDomain,
				UserId,
				NextTransactions
			);
		}

		return nullptr;
	}

	FAutoJobQueueDomain::FAutoJobQueueDomain(
		const FGs2Ptr& Gs2,
		const TFunction<TSharedPtr<FTransactionDomain>(
			const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
		)>& NewJobQueueDomain,
		const TFunction<TSharedPtr<FTransactionDomain>(
			bool bAutoRun,
			FString TransactionId,
			FString StampSheet,
			FString StampSheetEncryptionKeyId
		)>& NewTransactionDomain,
		const FString UserId,
		const FString NamespaceName,
		const FString JobName
	):
		FTransactionDomain(
			Gs2,
			NewJobQueueDomain,
			NewTransactionDomain,
			UserId,
			nullptr
		),
		NamespaceName(NamespaceName),
		JobName(JobName)
	{
            
	}

	FAutoJobQueueDomain::FAutoJobQueueDomain(
		const FAutoJobQueueDomain& From
	):
		FTransactionDomain(
			From.Gs2,
			From.NewJobQueueDomain,
			From.NewTransactionDomain,
			From.UserId,
			nullptr
		),
		NamespaceName(From.NamespaceName),
		JobName(From.JobName)
	{
	}

	Gs2::Core::Model::FGs2ErrorPtr FAutoJobQueueDomain::WaitImpl(
		const bool All,
		TSharedPtr<TSharedPtr<FTransactionDomain>> Result
	)
	{
		const auto Begin = FDateTime::Now();
	RETRY:
		if (FDateTime::Now() - Begin > FTimespan::FromSeconds(10)) {
			return MakeShared<Gs2::Core::Model::FUnknownError>(
				[]
				{
					auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
					Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(
						"unknown",
						"Failed to retrieve transaction results, either because there is some failure in GS2, or the GS2-Gateway used to notify the GS2-Distributor used to execute the transaction is not yet configured, or the GS2-Gateway has a user ID to receive notifications The configuration API may not have been invoked.",
						""
					));
					return Arr;
				}()
			);
		}
		const auto Future = Gs2->JobQueue->Namespace(
			NamespaceName
		)->User(
			UserId
		)->Job(
			JobName
		)->JobResult()->Model();
		Future->StartSynchronousTask();
		if (Future->GetTask().IsError())
		{
			return Future->GetTask().Error();
		}
		auto FutureResult = Future->GetTask().Result();
		if (!FutureResult.IsValid()) {
			FPlatformProcess::Sleep(0.01f);

			const auto Future2 = Gs2->JobQueue->DispatchByUserId(UserId);
			Future2->StartSynchronousTask();
			if (Future2->GetTask().IsError())
			{
				return Future2->GetTask().Error();
			}
			goto RETRY;
		}

		const auto Transaction = HandleResult(
			MakeShared<Gs2::JobQueue::Model::FJob>()
				->WithJobId(FutureResult->GetJobId())
				->WithName(Gs2::JobQueue::Model::FJob::GetJobNameFromGrn(*FutureResult->GetJobId()))
				->WithUserId(Gs2::JobQueue::Model::FJob::GetUserIdFromGrn(*FutureResult->GetJobId()))
				->WithScriptId(FutureResult->GetScriptId())
				->WithArgs(FutureResult->GetArgs()),
			MakeShared<Gs2::JobQueue::Model::FJobResultBody>()
				->WithTryNumber(FutureResult->GetTryNumber())
				->WithStatusCode(FutureResult->GetStatusCode())
				->WithResult(FutureResult->GetResult())
		);
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

	TSharedPtr<FAsyncTask<FTransactionDomain::FWaitTask>> FAutoJobQueueDomain::Wait(bool All)
	{
		return Gs2::Core::Util::New<FAsyncTask<FWaitTask>>(this->AsShared(), [this, All](
			TSharedPtr<TSharedPtr<FTransactionDomain>> Result
		) {
			return WaitImpl(All, Result);
		});
	}
}
