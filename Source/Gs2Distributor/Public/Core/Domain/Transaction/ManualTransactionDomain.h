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

#include "Gs2Core/Public/Core/Domain/Transaction/TransactionDomain.h"

namespace Gs2::Core::Domain
{
	class GS2DISTRIBUTOR_API FManualTransactionDomain:
		public FTransactionDomain
	{
	private:
	    static TMap<FString, FDateTime> Handled;
		FString TransactionId;
		FString StampSheet;
		FString StampSheetEncryptionKeyId;

		FTransactionDomainPtr HandleResult(
			FString Action,
			const TSharedPtr<FJsonObject>& ResultJson
        );

    public:
	    FManualTransactionDomain(
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
            const FString TransactionId,
			const FString StampSheet,
			const FString StampSheetEncryptionKeyId
        );
		FManualTransactionDomain(
			const FManualTransactionDomain& From
		);

	    virtual ~FManualTransactionDomain() override = default;

		Gs2::Core::Model::FGs2ErrorPtr WaitImpl(
			const bool All,
			TSharedPtr<TSharedPtr<FTransactionDomain>> Result
		);

        virtual TSharedPtr<FAsyncTask<FWaitTask>> Wait(
            bool All = false
        ) override;
	};
    typedef TSharedPtr<FManualTransactionDomain> FManualTransactionDomainPtr;
}
