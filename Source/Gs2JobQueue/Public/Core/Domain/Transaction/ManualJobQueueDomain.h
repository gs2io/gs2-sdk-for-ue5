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
#include "JobQueue/Model/Job.h"
#include "JobQueue/Model/JobResultBody.h"

namespace Gs2::Core::Domain
{
	class FManualJobQueueDomain: public FTransactionDomain
	{
	private:
		static TMap<FString, FDateTime> Handled;
	    FString NamespaceName;
	    FString JobName;

        FTransactionDomainPtr HandleResult(
	        const Gs2::JobQueue::Model::FJobPtr& Job,
	        const Gs2::JobQueue::Model::FJobResultBodyPtr& Result
        );

    public:
	
        FManualJobQueueDomain(
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
        );
		FManualJobQueueDomain(
			const FManualJobQueueDomain& From
		);

	    virtual ~FManualJobQueueDomain() override = default;

		Gs2::Core::Model::FGs2ErrorPtr WaitImpl(
			const bool All,
			TSharedPtr<TSharedPtr<FTransactionDomain>> Result
		);

	    virtual TSharedPtr<FAsyncTask<FWaitTask>> Wait(
            bool All = false
        ) override;
	};
    typedef TSharedPtr<FManualJobQueueDomain> FManualJobQueueDomainPtr;
}
