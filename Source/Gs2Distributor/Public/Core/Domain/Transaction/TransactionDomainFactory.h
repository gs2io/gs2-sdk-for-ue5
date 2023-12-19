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

#include "Gs2Core/Public/Core/Domain/Transaction/TransactionAccessTokenDomain.h"
#include "Gs2Core/Public/Core/Domain/Transaction/TransactionDomain.h"

namespace Gs2::Core::Domain
{
	class GS2DISTRIBUTOR_API FTransactionDomainFactory
	{
	public:
		static FTransactionAccessTokenDomainPtr ToTransaction(
			const FGs2Ptr& GS2,
			const TFunction<TSharedPtr<FTransactionAccessTokenDomain>(
				const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
			)>& NewJobQueueDomain,
			const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
			bool bAutoRun,
			FString TransactionId,
			FString StampSheet,
			FString StampSheetEncryptionKeyId
		);

		static FTransactionDomainPtr ToTransaction(
			const FGs2Ptr& GS2,
			const TFunction<TSharedPtr<FTransactionDomain>(
				const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
			)>& NewJobQueueDomain,
			FString UserId,
			bool bAutoRun,
			FString TransactionId,
			FString StampSheet,
			FString StampSheetEncryptionKeyId
		);
	};
    typedef TSharedPtr<FTransactionDomainFactory> FTransactionDomainFactoryPtr;
}
