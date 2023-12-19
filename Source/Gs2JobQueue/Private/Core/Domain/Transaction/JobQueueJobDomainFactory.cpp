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

#include "../Public/Core/Domain/Transaction/JobQueueJobDomainFactory.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/AutoJobQueueAccessTokenDomain.h"
#include "Core/Domain/Transaction/AutoJobQueueDomain.h"
#include "Core/Domain/Transaction/ManualJobQueueAccessTokenDomain.h"
#include "Core/Domain/Transaction/ManualJobQueueDomain.h"

namespace Gs2::Core::Domain
{
	FTransactionAccessTokenDomainPtr FJobQueueJobDomainFactory::ToTransaction(
		const FGs2Ptr& GS2,
		const TFunction<TSharedPtr<FTransactionAccessTokenDomain>(
			bool bAutoRun,
			FString TransactionId,
			FString StampSheet,
			FString StampSheetEncryptionKeyId
		)>& NewTransactionDomain,
		const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
		const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
	)
	{
		auto NewJobQueueDomain = [&](const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result)
		{
			return ToTransaction(
				GS2,
				NewTransactionDomain,
				AccessToken,
				Result
			);
		};
		if (Result->GetAutoRun()) {
			return MakeShared<FTransactionAccessTokenDomain>(
				GS2,
				NewJobQueueDomain,
				NewTransactionDomain,
				AccessToken,
				[&]
				{
					auto Arr = MakeShared<TArray<FTransactionAccessTokenDomainPtr>>();
					for (auto Item : *Result->GetItems())
					{
						Arr->Add(
							MakeShared<FAutoJobQueueAccessTokenDomain>(
								GS2,
								NewJobQueueDomain,
								NewTransactionDomain,
								AccessToken,
								*Gs2::JobQueue::Model::FJob::GetNamespaceNameFromGrn(*Item->GetJobId()),
								*Gs2::JobQueue::Model::FJob::GetJobNameFromGrn(*Item->GetJobId())
							)
						);
					}
					return Arr;
				}()
			);
		}
		else {
			for (auto Item : *Result->GetItems())
			{
				GS2->JobQueueDomain->Push(*Gs2::JobQueue::Model::FJob::GetNamespaceNameFromGrn(*Item->GetJobId()));
			}
			return MakeShared<FTransactionAccessTokenDomain>(
				GS2,
				NewJobQueueDomain,
				NewTransactionDomain,
				AccessToken,
				[&]
				{
					auto Arr = MakeShared<TArray<FTransactionAccessTokenDomainPtr>>();
					for (auto Item : *Result->GetItems())
					{
						Arr->Add(
							MakeShared<FManualJobQueueAccessTokenDomain>(
								GS2,
								NewJobQueueDomain,
								NewTransactionDomain,
								AccessToken,
								*Gs2::JobQueue::Model::FJob::GetNamespaceNameFromGrn(*Item->GetJobId()),
								*Gs2::JobQueue::Model::FJob::GetJobNameFromGrn(*Item->GetJobId())
							)
						);
					}
					return Arr;
				}()
			);
		}
	}

	FTransactionDomainPtr FJobQueueJobDomainFactory::ToTransaction(
		const FGs2Ptr& GS2,
		const TFunction<TSharedPtr<FTransactionDomain>(
			bool bAutoRun,
			FString TransactionId,
			FString StampSheet,
			FString StampSheetEncryptionKeyId
		)>& NewTransactionDomain,
		const FString UserId,
		const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
	)
	{
		auto NewJobQueueDomain = [&](const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result)
		{
			return ToTransaction(
				GS2,
				NewTransactionDomain,
				UserId,
				Result
			);
		};
		if (Result->GetAutoRun()) {
			return MakeShared<FTransactionDomain>(
				GS2,
				NewJobQueueDomain,
				NewTransactionDomain,
				UserId,
				[&]
				{
					auto Arr = MakeShared<TArray<FTransactionDomainPtr>>();
					for (auto Item : *Result->GetItems())
					{
						Arr->Add(
							MakeShared<FAutoJobQueueDomain>(
								GS2,
								NewJobQueueDomain,
								NewTransactionDomain,
								UserId,
								*Gs2::JobQueue::Model::FJob::GetNamespaceNameFromGrn(*Item->GetJobId()),
								*Gs2::JobQueue::Model::FJob::GetJobNameFromGrn(*Item->GetJobId())
							)
						);
					}
					return Arr;
				}()
			);
		}
		else {
			for (auto Item : *Result->GetItems())
			{
				GS2->JobQueueDomain->Push(*Gs2::JobQueue::Model::FJob::GetNamespaceNameFromGrn(*Item->GetJobId()));
			}
			return MakeShared<FTransactionDomain>(
				GS2,
				NewJobQueueDomain,
				NewTransactionDomain,
				UserId,
				[&]
				{
					auto Arr = MakeShared<TArray<FTransactionDomainPtr>>();
					for (auto Item : *Result->GetItems())
					{
						Arr->Add(
							MakeShared<FManualJobQueueDomain>(
								GS2,
								NewJobQueueDomain,
								NewTransactionDomain,
								UserId,
								*Gs2::JobQueue::Model::FJob::GetNamespaceNameFromGrn(*Item->GetJobId()),
								*Gs2::JobQueue::Model::FJob::GetJobNameFromGrn(*Item->GetJobId())
							)
						);
					}
					return Arr;
				}()
			);
		}
	}

	FTransactionAccessTokenDomainPtr FJobQueueJobDomainFactory::ToTransaction(
		const FGs2Ptr& GS2,
		const TFunction<TSharedPtr<FTransactionAccessTokenDomain>(
			bool bAutoRun,
			FString TransactionId,
			FString StampSheet,
			FString StampSheetEncryptionKeyId
		)>& NewTransactionDomain,
		const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
		bool bAutoRun,
		FString NamespaceName,
		FString JobName
	)
	{
		auto NewJobQueueDomain = [&](const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result)
		{
			return ToTransaction(
				GS2,
				NewTransactionDomain,
				AccessToken,
				Result
			);
		};
		if (bAutoRun) {
			return MakeShared<FTransactionAccessTokenDomain>(
				GS2,
				NewJobQueueDomain,
				NewTransactionDomain,
				AccessToken,
				[&]
				{
					auto Arr = MakeShared<TArray<FTransactionAccessTokenDomainPtr>>();
					Arr->Add(
						MakeShared<FAutoJobQueueAccessTokenDomain>(
							GS2,
							NewJobQueueDomain,
							NewTransactionDomain,
							AccessToken,
							NamespaceName,
							JobName
						)
					);
					return Arr;
				}()
			);
		}
		else {
			GS2->JobQueueDomain->Push(NamespaceName);
			return MakeShared<FTransactionAccessTokenDomain>(
				GS2,
				NewJobQueueDomain,
				NewTransactionDomain,
				AccessToken,
				[&]
				{
					auto Arr = MakeShared<TArray<FTransactionAccessTokenDomainPtr>>();
					Arr->Add(
						MakeShared<FManualJobQueueAccessTokenDomain>(
							GS2,
							NewJobQueueDomain,
							NewTransactionDomain,
							AccessToken,
							NamespaceName,
							JobName
						)
					);
					return Arr;
				}()
			);
		}
	}

	FTransactionDomainPtr FJobQueueJobDomainFactory::ToTransaction(
		const FGs2Ptr& GS2,
		const TFunction<TSharedPtr<FTransactionDomain>(
			bool bAutoRun,
			FString TransactionId,
			FString StampSheet,
			FString StampSheetEncryptionKeyId
		)>& NewTransactionDomain,
		const FString UserId,
		bool bAutoRun,
		FString NamespaceName,
		FString JobName
	)
	{
		auto NewJobQueueDomain = [&](const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result)
		{
			return ToTransaction(
				GS2,
				NewTransactionDomain,
				UserId,
				Result
			);
		};
		if (bAutoRun) {
			return MakeShared<FTransactionDomain>(
				GS2,
				NewJobQueueDomain,
				NewTransactionDomain,
				UserId,
				[&]
				{
					auto Arr = MakeShared<TArray<FTransactionDomainPtr>>();
					Arr->Add(
						MakeShared<FAutoJobQueueDomain>(
							GS2,
							NewJobQueueDomain,
							NewTransactionDomain,
							UserId,
							NamespaceName,
							JobName
						)
					);
					return Arr;
				}()
			);
		}
		else {
			GS2->JobQueueDomain->Push(NamespaceName);
			return MakeShared<FTransactionDomain>(
				GS2,
				NewJobQueueDomain,
				NewTransactionDomain,
				UserId,
				[&]
				{
					auto Arr = MakeShared<TArray<FTransactionDomainPtr>>();
					Arr->Add(
						MakeShared<FManualJobQueueDomain>(
							GS2,
							NewJobQueueDomain,
							NewTransactionDomain,
							UserId,
							NamespaceName,
							JobName
						)
					);
					return Arr;
				}()
			);
		}
	}
}