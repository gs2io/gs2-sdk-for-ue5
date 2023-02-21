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

#include "CoreMinimal.h"
#include "Core/Domain/Model/JobQueueDomain.h"
#include "Core/Domain/CacheDatabase.h"
#include "Core/Domain/Model/StampSheetConfiguration.h"
#include "Core/Net/Rest/Gs2RestSession.h"

namespace Gs2::Core::Domain::Model
{
    class GS2DISTRIBUTOR_API FAutoStampSheetDomain :
        public TSharedFromThis<FAutoStampSheetDomain>
    {
        Gs2::Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        FString DistributorNamespaceName;
        FString TransactionId;
        FStampSheetConfigurationPtr StampSheetConfiguration;
        
    public:
        FAutoStampSheetDomain(
            const Gs2::Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Net::Rest::FGs2RestSessionPtr Session,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
            const FString DistributorNamespaceName,
            const FString TransactionId,
            const FStampSheetConfigurationPtr StampSheetConfiguration
        );
        FAutoStampSheetDomain(
            const FAutoStampSheetDomain& From
        );
        ~FAutoStampSheetDomain() = default;

        class FRunTask final :
            public Gs2::Core::Util::TGs2Future<void*>,
            public TSharedFromThis<FRunTask>
        {
            const TSharedPtr<FAutoStampSheetDomain> Self;
        public:
            explicit FRunTask(
                const TSharedPtr<FAutoStampSheetDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<void*>> Result
            ) override;
        };
        friend FRunTask;

        TSharedPtr<FAsyncTask<FRunTask>> Run();
    };
    typedef TSharedPtr<FAutoStampSheetDomain> FAutoStampSheetDomainPtr;
}
