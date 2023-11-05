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

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
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

    class GS2MEGAFIELD_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::MegaField::FGs2MegaFieldRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FUserDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        class GS2MEGAFIELD_API FFetchPositionFromSystemTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>,
            public TSharedFromThis<FFetchPositionFromSystemTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FFetchPositionFromSystemRequestPtr Request;
        public:
            explicit FFetchPositionFromSystemTask(
                const TSharedPtr<FUserDomain> Self,
                const Request::FFetchPositionFromSystemRequestPtr Request
            );

            FFetchPositionFromSystemTask(
                const FFetchPositionFromSystemTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>> Result
            ) override;
        };
        friend FFetchPositionFromSystemTask;

        TSharedPtr<FAsyncTask<FFetchPositionFromSystemTask>> FetchPositionFromSystem(
            Request::FFetchPositionFromSystemRequestPtr Request
        );

        class GS2MEGAFIELD_API FNearUserIdsFromSystemTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>,
            public TSharedFromThis<FNearUserIdsFromSystemTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FNearUserIdsFromSystemRequestPtr Request;
        public:
            explicit FNearUserIdsFromSystemTask(
                const TSharedPtr<FUserDomain> Self,
                const Request::FNearUserIdsFromSystemRequestPtr Request
            );

            FNearUserIdsFromSystemTask(
                const FNearUserIdsFromSystemTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>> Result
            ) override;
        };
        friend FNearUserIdsFromSystemTask;

        TSharedPtr<FAsyncTask<FNearUserIdsFromSystemTask>> NearUserIdsFromSystem(
            Request::FNearUserIdsFromSystemRequestPtr Request
        );

        TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain> Spatial(
            const FString AreaModelName,
            const FString LayerModelName
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserDomain> FUserDomainPtr;
}
