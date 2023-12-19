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

#include "Gs2JobQueue/Public/JobQueue/Result/PushByUserIdResult.h"
#include "Gs2Core/Public/Core/Util/Gs2Future.h"

namespace Gs2::Core::Domain
{
	class FGs2;
	typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Core::Domain
{
	class GS2CORE_API FTransactionDomain:
		public TSharedFromThis<FTransactionDomain>
	{
	public:
		const FGs2Ptr Gs2;
		const TFunction<TSharedPtr<FTransactionDomain>(
			const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
		)> NewJobQueueDomain;
		const TFunction<TSharedPtr<FTransactionDomain>(
			bool bAutoRun,
			FString TransactionId,
			FString StampSheet,
			FString StampSheetEncryptionKeyId
		)> NewTransactionDomain;
		const FString UserId;
		const TSharedPtr<TArray<TSharedPtr<FTransactionDomain>>> Actions;

        FTransactionDomain(
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
	        const TSharedPtr<TArray<TSharedPtr<FTransactionDomain>>>& Actions
        );
		FTransactionDomain(
			const FTransactionDomain& From
		);

	    virtual ~FTransactionDomain() = default;

		Gs2::Core::Model::FGs2ErrorPtr WaitImpl(
			const bool All,
			TSharedPtr<TSharedPtr<FTransactionDomain>> Result
		) const;

	    class GS2CORE_API FWaitTask :
            public Gs2::Core::Util::TGs2Future<FTransactionDomain>,
            public TSharedFromThis<FWaitTask>
        {
	    protected:
            const TSharedPtr<FTransactionDomain> Self;
	    	const TFunction<Gs2::Core::Model::FGs2ErrorPtr(
				TSharedPtr<TSharedPtr<FTransactionDomain>>
			)> Func;
        public:
            explicit FWaitTask(
	            const TSharedPtr<FTransactionDomain>& Self,
				const TFunction<Gs2::Core::Model::FGs2ErrorPtr(
					TSharedPtr<TSharedPtr<FTransactionDomain>>
				)> Func
            );

            FWaitTask(
                const FWaitTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FTransactionDomain>> Result
            ) override;
        };
	    friend FWaitTask;

        virtual TSharedPtr<FAsyncTask<FWaitTask>> Wait(
            bool All = false
        );
	};
    typedef TSharedPtr<FTransactionDomain> FTransactionDomainPtr;
}
