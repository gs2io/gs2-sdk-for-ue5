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

#include "../Public/Core/Domain/Transaction/TransactionAccessTokenDomain.h"

namespace Gs2::Core::Domain
{
	FTransactionAccessTokenDomain::FTransactionAccessTokenDomain(
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
		const TSharedPtr<TArray<TSharedPtr<FTransactionAccessTokenDomain>>>& Actions
	):
		Gs2(Gs2),
		NewJobQueueDomain(NewJobQueueDomain),
		NewTransactionDomain(NewTransactionDomain),
		AccessToken(AccessToken),
		Actions(Actions)
	{

	}

	FTransactionAccessTokenDomain::FTransactionAccessTokenDomain(
		const FTransactionAccessTokenDomain& From
	):
		Gs2(From.Gs2),
		NewJobQueueDomain(From.NewJobQueueDomain),
		NewTransactionDomain(From.NewTransactionDomain),
		AccessToken(From.AccessToken),
		Actions(From.Actions)
	{
	}

	Gs2::Core::Model::FGs2ErrorPtr FTransactionAccessTokenDomain::WaitImpl(
		const bool All,
		TSharedPtr<TSharedPtr<FTransactionAccessTokenDomain>> Result
	) const
	{
		if (Actions->Num() == 0) {
			return nullptr;
		}
		const auto NextActions = MakeShared<TArray<TSharedPtr<FTransactionAccessTokenDomain>>>();
		for (auto Action : *Actions) {
			const auto InnerFuture = Action->Wait();
			InnerFuture->StartSynchronousTask();
			if (InnerFuture->GetTask().IsError())
			{
				return InnerFuture->GetTask().Error();
			}
			auto InnerNext = InnerFuture->GetTask().Result();
			if (InnerNext.IsValid()) {
				NextActions->Add(InnerNext);
			}
		}
		const auto Next = MakeShared<FTransactionAccessTokenDomain>(
			Gs2,
			NewJobQueueDomain,
			NewTransactionDomain,
			AccessToken,
			NextActions
		);
		const auto NextFuture = Next->Wait(true);
		NextFuture->StartSynchronousTask();
		if (NextFuture->GetTask().IsError())
		{
			return NextFuture->GetTask().Error();
		}
		return nullptr;
	}

	FTransactionAccessTokenDomain::FWaitTask::FWaitTask(
		const TSharedPtr<FTransactionAccessTokenDomain>& Self,
		TFunction<Gs2::Core::Model::FGs2ErrorPtr(
			TSharedPtr<TSharedPtr<FTransactionAccessTokenDomain>>
		)> Func
	):
		Self(Self),
		Func(Func)
	{
	}

	FTransactionAccessTokenDomain::FWaitTask::FWaitTask(const FWaitTask& From):
		Self(From.Self),
		Func(From.Func)
	{
	}

	Gs2::Core::Model::FGs2ErrorPtr FTransactionAccessTokenDomain::FWaitTask::Action(
		TSharedPtr<TSharedPtr<FTransactionAccessTokenDomain>> Result)
	{
		return Func(
			Result
		);
	}

	TSharedPtr<FAsyncTask<FTransactionAccessTokenDomain::FWaitTask>> FTransactionAccessTokenDomain::Wait(
		bool All
	) {
		return Gs2::Core::Util::New<FAsyncTask<FWaitTask>>(this->AsShared(), [this, All](
			TSharedPtr<TSharedPtr<FTransactionAccessTokenDomain>> Result
		) {
			return WaitImpl(All, Result);
		});
	}
}
