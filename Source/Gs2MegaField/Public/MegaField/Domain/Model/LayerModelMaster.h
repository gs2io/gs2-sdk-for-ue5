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
#include "MegaField/Domain/Iterator/DescribeNamespacesIterator.h"
#include "MegaField/Domain/Iterator/DescribeAreaModelsIterator.h"
#include "MegaField/Domain/Iterator/DescribeAreaModelMastersIterator.h"
#include "MegaField/Domain/Iterator/DescribeLayerModelsIterator.h"
#include "MegaField/Domain/Iterator/DescribeLayerModelMastersIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::MegaField::Domain
{
    class FGs2MegaFieldDomain;
    typedef TSharedPtr<FGs2MegaFieldDomain> FGs2MegaFieldDomainPtr;
}

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

    class GS2MEGAFIELD_API FLayerModelMasterDomain:
        public TSharedFromThis<FLayerModelMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const MegaField::Domain::FGs2MegaFieldDomainPtr Service;
        const Gs2::MegaField::FGs2MegaFieldRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> AreaModelName;
        TOptional<FString> LayerModelName;
    private:

        FString ParentKey;

    public:

        FLayerModelMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const MegaField::Domain::FGs2MegaFieldDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> AreaModelName,
            const TOptional<FString> LayerModelName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FLayerModelMasterDomain(
            const FLayerModelMasterDomain& From
        );

        class GS2MEGAFIELD_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::MegaField::Model::FLayerModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FLayerModelMasterDomain> Self;
            const Request::FGetLayerModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FLayerModelMasterDomain>& Self,
                const Request::FGetLayerModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FLayerModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetLayerModelMasterRequestPtr Request
        );

        class GS2MEGAFIELD_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::MegaField::Domain::Model::FLayerModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FLayerModelMasterDomain> Self;
            const Request::FUpdateLayerModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FLayerModelMasterDomain>& Self,
                const Request::FUpdateLayerModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FLayerModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateLayerModelMasterRequestPtr Request
        );

        class GS2MEGAFIELD_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::MegaField::Domain::Model::FLayerModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FLayerModelMasterDomain> Self;
            const Request::FDeleteLayerModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FLayerModelMasterDomain>& Self,
                const Request::FDeleteLayerModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FLayerModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteLayerModelMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> AreaModelName,
            TOptional<FString> LayerModelName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> LayerModelName
        );

        class GS2MEGAFIELD_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::MegaField::Model::FLayerModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FLayerModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FLayerModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FLayerModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::MegaField::Model::FLayerModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FLayerModelMasterDomain> FLayerModelMasterDomainPtr;
}
