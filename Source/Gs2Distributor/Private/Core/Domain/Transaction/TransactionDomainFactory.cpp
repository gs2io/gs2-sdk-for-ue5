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

#include "../Public/Core/Domain/Transaction/TransactionDomainFactory.h"

#include "Core/Domain/Transaction/AutoTransactionAccessTokenDomain.h"
#include "Core/Domain/Transaction/AutoTransactionDomain.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"

namespace Gs2::Core::Domain
{
	FTransactionAccessTokenDomainPtr FTransactionDomainFactory::ToTransaction(
		const FGs2Ptr& GS2,
		const TFunction<TSharedPtr<FTransactionAccessTokenDomain>(
			const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
		)>& NewJobQueueDomain,
		const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
		bool bAutoRun,
		FString TransactionId,
		FString StampSheet,
		FString StampSheetEncryptionKeyId,
		bool bAtomicCommit,
		Gs2::Core::Model::FTransactionResultPtr TransactionResult
	)
	{
		auto NewTransactionDomain = [&](
			bool bAutoRun,
			FString TransactionId,
			FString StampSheet,
			FString StampSheetEncryptionKeyId,
			bool bAtomicCommit,
			Gs2::Core::Model::FTransactionResultPtr TransactionResult
		)
		{
			return ToTransaction(
				GS2,
				NewJobQueueDomain,
				AccessToken,
				bAutoRun,
				TransactionId,
				StampSheet,
				StampSheetEncryptionKeyId,
				bAtomicCommit,
				TransactionResult
			);
		};
		if (bAutoRun) {
			return MakeShared<FAutoTransactionAccessTokenDomain>(
				GS2,
				NewJobQueueDomain,
				NewTransactionDomain,
				AccessToken,
				TransactionId
			);
		}
		else {
			return MakeShared<FManualTransactionAccessTokenDomain>(
				GS2,
				NewJobQueueDomain,
				NewTransactionDomain,
				AccessToken,
				TransactionId,
				StampSheet,
				StampSheetEncryptionKeyId
			);
		}
	}

	FTransactionDomainPtr FTransactionDomainFactory::ToTransaction(
		const FGs2Ptr& GS2,
		const TFunction<TSharedPtr<FTransactionDomain>(
			const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
		)>& NewJobQueueDomain,
		FString UserId,
		bool bAutoRun,
		FString TransactionId,
		FString StampSheet,
		FString StampSheetEncryptionKeyId,
		bool bAtomicCommit,
		Gs2::Core::Model::FTransactionResultPtr TransactionResult
	)
	{
		auto NewTransactionDomain = [&GS2, NewJobQueueDomain, UserId](
			bool bAutoRun,
			FString TransactionId,
			FString StampSheet,
			FString StampSheetEncryptionKeyId,
			bool bAtomicCommit,
			Gs2::Core::Model::FTransactionResultPtr TransactionResult
		)
		{
			return ToTransaction(
				GS2,
				NewJobQueueDomain,
				UserId,
				bAutoRun,
				TransactionId,
				StampSheet,
				StampSheetEncryptionKeyId,
				bAtomicCommit,
				TransactionResult
			);
		};
		if (bAutoRun) {
			return MakeShared<FAutoTransactionDomain>(
				GS2,
				NewJobQueueDomain,
				NewTransactionDomain,
				UserId,
				TransactionId
			);
		}
		else {
			return MakeShared<FManualTransactionDomain>(
				GS2,
				NewJobQueueDomain,
				NewTransactionDomain,
				UserId,
				TransactionId,
				StampSheet,
				StampSheetEncryptionKeyId
			);
		}
	}
}