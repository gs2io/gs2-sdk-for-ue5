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

#include "HAL/CriticalSection.h"
#include "Distributor/Model/StampSheetResult.h"
#include "Distributor/Model/TransactionResult.h"
#include "Core/Domain/Transaction/TransactionAccessTokenDomain.h"

namespace Gs2::Core::Domain
{
	class GS2DISTRIBUTOR_API FAutoTransactionAccessTokenDomain:
		public FTransactionAccessTokenDomain
	{
	private:
	    static TMap<FString, FDateTime> Handled;
        static FCriticalSection HandledMutex;
        FString TransactionId;
        TOptional<FString> TransactionNamespaceName;
        const bool bAtomicCommit;
        const Gs2::Core::Model::FTransactionResultPtr InitialTransactionResult;
        FCriticalSection TransactionResultMutex;
        bool bTransactionResultHandled;

        FTransactionAccessTokenDomainPtr HandleResult(
            Gs2::Distributor::Model::FStampSheetResultPtr Result,
            Gs2::Core::Model::FGs2ErrorPtr& Error
        );

        FTransactionAccessTokenDomainPtr HandleTransactionResult(
            Gs2::Distributor::Model::FTransactionResultPtr Result,
            Gs2::Core::Model::FGs2ErrorPtr& Error
        );

        bool MarkHandled();
        bool MarkTransactionResultHandled();

    public:
	    FAutoTransactionAccessTokenDomain(
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
            const TFunction<Gs2::Core::Model::FGs2ErrorPtr(
                const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
            )>& Dispatch,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const FString TransactionId,
            const bool bAtomicCommit = false,
            const Gs2::Core::Model::FTransactionResultPtr InitialTransactionResult = nullptr,
            const TOptional<FString> NamespaceName = TOptional<FString>()
        );
		FAutoTransactionAccessTokenDomain(
			const FAutoTransactionAccessTokenDomain& From
		);

	    virtual ~FAutoTransactionAccessTokenDomain() override = default;

		virtual TOptional<FString> GetTransactionId() const override;

		Gs2::Core::Model::FGs2ErrorPtr WaitImpl(
			const bool All,
			TSharedPtr<TSharedPtr<FTransactionAccessTokenDomain>> Result
		);

        virtual TSharedPtr<FAsyncTask<FWaitTask>> Wait(
            bool All = false
        ) override;
	};
    typedef TSharedPtr<FAutoTransactionAccessTokenDomain> FAutoTransactionAccessTokenDomainPtr;
}
