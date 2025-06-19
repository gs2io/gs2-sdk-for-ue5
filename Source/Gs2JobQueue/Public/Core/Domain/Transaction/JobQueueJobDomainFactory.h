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

#pragma once

#include "Core/Domain/Transaction/TransactionAccessTokenDomain.h"
#include "Core/Domain/Transaction/TransactionDomain.h"
#include "JobQueue/Result/PushByUserIdResult.h"

namespace Gs2::Core::Domain
{
	class GS2JOBQUEUE_API FJobQueueJobDomainFactory
	{
	public:
		static FTransactionAccessTokenDomainPtr ToTransaction(
			const FGs2Ptr& GS2,
			const TFunction<TSharedPtr<FTransactionAccessTokenDomain>(
				bool bAutoRun,
				FString TransactionId,
				FString StampSheet,
				FString StampSheetEncryptionKeyId,
				bool bAtomicCommit,
				Gs2::Core::Model::FTransactionResultPtr TransactionResult
			)>& NewTransactionDomain,
			const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
			const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
		);

		static FTransactionDomainPtr ToTransaction(
			const FGs2Ptr& GS2,
			const TFunction<TSharedPtr<FTransactionDomain>(
				bool bAutoRun,
				FString TransactionId,
				FString StampSheet,
				FString StampSheetEncryptionKeyId,
				bool bAtomicCommit,
				Gs2::Core::Model::FTransactionResultPtr TransactionResult
			)>& NewTransactionDomain,
			const FString UserId,
			const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
		);
		
		static FTransactionAccessTokenDomainPtr ToTransaction(
			const FGs2Ptr& GS2,
			const TFunction<TSharedPtr<FTransactionAccessTokenDomain>(
				bool bAutoRun,
				FString TransactionId,
				FString StampSheet,
				FString StampSheetEncryptionKeyId,
				bool bAtomicCommit,
				Gs2::Core::Model::FTransactionResultPtr TransactionResult
			)>& NewTransactionDomain,
			const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
			bool bAutoRun,
			FString NamespaceName,
			FString JobName
		);

		static FTransactionDomainPtr ToTransaction(
			const FGs2Ptr& GS2,
			const TFunction<TSharedPtr<FTransactionDomain>(
				bool bAutoRun,
				FString TransactionId,
				FString StampSheet,
				FString StampSheetEncryptionKeyId,
				bool bAtomicCommit,
				Gs2::Core::Model::FTransactionResultPtr TransactionResult
			)>& NewTransactionDomain,
			const FString UserId,
			bool bAutoRun,
			FString NamespaceName,
			FString JobName
		);
    };
}
