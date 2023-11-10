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
#include "Formation/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Formation/Domain/Iterator/DescribeFormModelMastersIterator.h"
#include "Formation/Domain/Iterator/DescribeMoldModelsIterator.h"
#include "Formation/Domain/Iterator/DescribeMoldModelMastersIterator.h"
#include "Formation/Domain/Iterator/DescribePropertyFormModelsIterator.h"
#include "Formation/Domain/Iterator/DescribePropertyFormModelMastersIterator.h"
#include "Formation/Domain/Iterator/DescribeMoldsIterator.h"
#include "Formation/Domain/Iterator/DescribeMoldsByUserIdIterator.h"
#include "Formation/Domain/Iterator/DescribeFormsIterator.h"
#include "Formation/Domain/Iterator/DescribeFormsByUserIdIterator.h"
#include "Formation/Domain/Iterator/DescribePropertyFormsIterator.h"
#include "Formation/Domain/Iterator/DescribePropertyFormsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Formation::Domain
{
    class FGs2FormationDomain;
    typedef TSharedPtr<FGs2FormationDomain> FGs2FormationDomainPtr;
}

namespace Gs2::Formation::Domain::Model
{
    class FNamespaceDomain;
    class FFormModelDomain;
    class FFormModelMasterDomain;
    class FMoldModelDomain;
    class FMoldModelMasterDomain;
    class FPropertyFormModelDomain;
    class FPropertyFormModelMasterDomain;
    class FCurrentFormMasterDomain;
    class FMoldDomain;
    class FMoldAccessTokenDomain;
    class FFormDomain;
    class FFormAccessTokenDomain;
    class FPropertyFormDomain;
    class FPropertyFormAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2FORMATION_API FFormModelMasterDomain:
        public TSharedFromThis<FFormModelMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Formation::Domain::FGs2FormationDomainPtr Service;
        const Gs2::Formation::FGs2FormationRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> FormModelName;
    private:

        FString ParentKey;

    public:

        FFormModelMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Formation::Domain::FGs2FormationDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> FormModelName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FFormModelMasterDomain(
            const FFormModelMasterDomain& From
        );

        class GS2FORMATION_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Model::FFormModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FFormModelMasterDomain> Self;
            const Request::FGetFormModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FFormModelMasterDomain>& Self,
                const Request::FGetFormModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Model::FFormModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetFormModelMasterRequestPtr Request
        );

        class GS2FORMATION_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FFormModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FFormModelMasterDomain> Self;
            const Request::FUpdateFormModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FFormModelMasterDomain>& Self,
                const Request::FUpdateFormModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateFormModelMasterRequestPtr Request
        );

        class GS2FORMATION_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FFormModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FFormModelMasterDomain> Self;
            const Request::FDeleteFormModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FFormModelMasterDomain>& Self,
                const Request::FDeleteFormModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteFormModelMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> FormModelName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> FormModelName
        );

        class GS2FORMATION_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Model::FFormModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FFormModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FFormModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Model::FFormModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Formation::Model::FFormModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FFormModelMasterDomain> FFormModelMasterDomainPtr;
}
