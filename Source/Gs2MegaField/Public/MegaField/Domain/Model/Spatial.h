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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "MegaField/Gs2MegaField.h"
#include "MegaField/Domain/Iterator/DescribeNamespacesIterator.h"
#include "MegaField/Domain/Iterator/DescribeAreaModelsIterator.h"
#include "MegaField/Domain/Iterator/DescribeAreaModelMastersIterator.h"
#include "MegaField/Domain/Iterator/DescribeLayerModelsIterator.h"
#include "MegaField/Domain/Iterator/DescribeLayerModelMastersIterator.h"

namespace Gs2::MegaField::Domain::Model
{
    class FNamespaceDomain;
    class FAreaModelDomain;
    class FAreaModelMasterDomain;
    class FLayerModelDomain;
    class FLayerModelMasterDomain;
    class FCurrentFieldMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FSpatialDomain;
    class FSpatialAccessTokenDomain;

    class GS2MEGAFIELD_API FSpatialDomain:
        public TSharedFromThis<FSpatialDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::MegaField::FGs2MegaFieldRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> AreaModelName;
        TOptional<FString> LayerModelName;
    private:

        FString ParentKey;

    public:

        FSpatialDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> AreaModelName,
            const TOptional<FString> LayerModelName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSpatialDomain(
            const FSpatialDomain& From
        );

        class GS2MEGAFIELD_API FPutPositionTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::MegaField::Domain::Model::FSpatialDomain>,
            public TSharedFromThis<FPutPositionTask>
        {
            const TSharedPtr<FSpatialDomain> Self;
            const Request::FPutPositionByUserIdRequestPtr Request;
        public:
            explicit FPutPositionTask(
                const TSharedPtr<FSpatialDomain> Self,
                const Request::FPutPositionByUserIdRequestPtr Request
            );

            FPutPositionTask(
                const FPutPositionTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>> Result
            ) override;
        };
        friend FPutPositionTask;

        TSharedPtr<FAsyncTask<FPutPositionTask>> PutPosition(
            Request::FPutPositionByUserIdRequestPtr Request
        );

        class GS2MEGAFIELD_API FActionTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>,
            public TSharedFromThis<FActionTask>
        {
            const TSharedPtr<FSpatialDomain> Self;
            const Request::FActionByUserIdRequestPtr Request;
        public:
            explicit FActionTask(
                const TSharedPtr<FSpatialDomain> Self,
                const Request::FActionByUserIdRequestPtr Request
            );

            FActionTask(
                const FActionTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>> Result
            ) override;
        };
        friend FActionTask;

        TSharedPtr<FAsyncTask<FActionTask>> Action(
            Request::FActionByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> AreaModelName,
            TOptional<FString> LayerModelName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> AreaModelName,
            TOptional<FString> LayerModelName
        );

        class GS2MEGAFIELD_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::MegaField::Model::FSpatial>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FSpatialDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FSpatialDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FSpatial>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FSpatialDomain> FSpatialDomainPtr;
}
