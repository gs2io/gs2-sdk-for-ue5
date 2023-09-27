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
 *
 * deny overwrite
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

    class GS2MEGAFIELD_API FSpatialAccessTokenDomain:
        public TSharedFromThis<FSpatialAccessTokenDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::MegaField::FGs2MegaFieldRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> AreaModelName;
        TOptional<FString> LayerModelName;
    private:

        FString ParentKey;

    public:

        FSpatialAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
            const TOptional<FString> AreaModelName,
            const TOptional<FString> LayerModelName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSpatialAccessTokenDomain(
            const FSpatialAccessTokenDomain& From
        );

        class GS2MEGAFIELD_API FPutPositionTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::MegaField::Domain::Model::FSpatialAccessTokenDomain>,
            public TSharedFromThis<FPutPositionTask>
        {
            const TSharedPtr<FSpatialAccessTokenDomain> Self;
            const Request::FPutPositionRequestPtr Request;
        public:
            explicit FPutPositionTask(
                const TSharedPtr<FSpatialAccessTokenDomain> Self,
                const Request::FPutPositionRequestPtr Request
            );

            FPutPositionTask(
                const FPutPositionTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialAccessTokenDomain>> Result
            ) override;
        };
        friend FPutPositionTask;

        TSharedPtr<FAsyncTask<FPutPositionTask>> PutPosition(
            Request::FPutPositionRequestPtr Request
        );

        class GS2MEGAFIELD_API FFetchPositionTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>,
            public TSharedFromThis<FFetchPositionTask>
        {
            const TSharedPtr<FSpatialAccessTokenDomain> Self;
            const Request::FFetchPositionRequestPtr Request;
        public:
            explicit FFetchPositionTask(
                const TSharedPtr<FSpatialAccessTokenDomain> Self,
                const Request::FFetchPositionRequestPtr Request
            );

            FFetchPositionTask(
                const FFetchPositionTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>> Result
            ) override;
        };
        friend FFetchPositionTask;

        TSharedPtr<FAsyncTask<FFetchPositionTask>> FetchPosition(
            Request::FFetchPositionRequestPtr Request
        );

        class GS2MEGAFIELD_API FNearUserIdsTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialAccessTokenDomain>>>,
            public TSharedFromThis<FNearUserIdsTask>
        {
            const TSharedPtr<FSpatialAccessTokenDomain> Self;
            const Request::FNearUserIdsRequestPtr Request;
        public:
            explicit FNearUserIdsTask(
                const TSharedPtr<FSpatialAccessTokenDomain> Self,
                const Request::FNearUserIdsRequestPtr Request
            );

            FNearUserIdsTask(
                const FNearUserIdsTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialAccessTokenDomain>>>> Result
            ) override;
        };
        friend FNearUserIdsTask;

        TSharedPtr<FAsyncTask<FNearUserIdsTask>> NearUserIds(
            Request::FNearUserIdsRequestPtr Request
        );

        class GS2MEGAFIELD_API FActionTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>,
            public TSharedFromThis<FActionTask>
        {
            const TSharedPtr<FSpatialAccessTokenDomain> Self;
            const Request::FActionRequestPtr Request;
        public:
            explicit FActionTask(
                const TSharedPtr<FSpatialAccessTokenDomain> Self,
                const Request::FActionRequestPtr Request
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
            Request::FActionRequestPtr Request
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
            const TSharedPtr<FSpatialAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FSpatialAccessTokenDomain> Self
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

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::MegaField::Model::FSpatialPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FSpatialAccessTokenDomain> FSpatialAccessTokenDomainPtr;
}
