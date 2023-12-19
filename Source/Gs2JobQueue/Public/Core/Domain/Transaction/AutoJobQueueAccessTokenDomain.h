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
#include "JobQueue/Model/Job.h"
#include "JobQueue/Model/JobResultBody.h"

namespace Gs2::Core::Domain
{
	class FAutoJobQueueAccessTokenDomain: public FTransactionAccessTokenDomain
	{
	private:
		static TMap<FString, FDateTime> Handled;
	    FString NamespaceName;
	    FString JobName;

        FTransactionAccessTokenDomainPtr HandleResult(
	        const Gs2::JobQueue::Model::FJobPtr& Job,
	        const Gs2::JobQueue::Model::FJobResultBodyPtr& Result
        );

    public:
	
		FAutoJobQueueAccessTokenDomain(
			const FGs2Ptr& Gs2,
			const TFunction<TSharedPtr<FTransactionAccessTokenDomain>(
				const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
			)>& NewJobQueueDomain,
			const TFunction<TSharedPtr<FTransactionAccessTokenDomain>(
				bool bAutoRun,
				FString TransactionId,
				FString StampSheet,
				FString StampSheetEncryptionKeyId
			)>& NewTransactionDomain,
			const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
			const FString NamespaceName,
			const FString JobName
		);
		FAutoJobQueueAccessTokenDomain(
			const FAutoJobQueueAccessTokenDomain& From
		);

	    virtual ~FAutoJobQueueAccessTokenDomain() override = default;

		Gs2::Core::Model::FGs2ErrorPtr WaitImpl(
			const bool All,
			TSharedPtr<TSharedPtr<FTransactionAccessTokenDomain>> Result
		);

	    virtual TSharedPtr<FAsyncTask<FWaitTask>> Wait(
            bool All = false
        ) override;
	};
    typedef TSharedPtr<FAutoJobQueueAccessTokenDomain> FAutoJobQueueAccessTokenDomainPtr;
}
