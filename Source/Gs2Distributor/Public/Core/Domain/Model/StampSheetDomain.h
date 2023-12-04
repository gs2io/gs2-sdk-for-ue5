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
#include "Core/Domain/Model/TransactionConfiguration.h"
#include "Core/Net/Rest/Gs2RestSession.h"

namespace Gs2::Core::Domain::Model
{
    class GS2DISTRIBUTOR_API FStampSheetDomain :
        public TSharedFromThis<FStampSheetDomain>
    {
        Gs2::Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        FString StampSheet;
        FString StampSheetEncryptionKeyId;
        FTransactionConfigurationPtr StampSheetConfiguration;
        
    public:
        FStampSheetDomain(
            const Gs2::Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Net::Rest::FGs2RestSessionPtr Session,
            const FString StampSheet,
            const FString StampSheetEncryptionKeyId,
            const FTransactionConfigurationPtr StampSheetConfiguration
        );
        FStampSheetDomain(const FStampSheetDomain& From);
        ~FStampSheetDomain() = default;

        class GS2DISTRIBUTOR_API FRunTask final :
            public Gs2::Core::Util::TGs2Future<void*>,
            public TSharedFromThis<FRunTask>
        {
            const TSharedPtr<FStampSheetDomain> Self;
        public:
            explicit FRunTask(
                const TSharedPtr<FStampSheetDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<void*>> Result
            ) override;
        };
        friend FRunTask;

        TSharedPtr<FAsyncTask<FRunTask>> Run();
    };
    typedef TSharedPtr<FStampSheetDomain> FStampSheetDomainPtr;
}
