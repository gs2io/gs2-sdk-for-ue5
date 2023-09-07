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
#include "Formation/Gs2Formation.h"
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

    class GS2FORMATION_API FMoldModelDomain:
        public TSharedFromThis<FMoldModelDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Formation::FGs2FormationRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> MoldModelName;
    private:

        FString ParentKey;

    public:

        FMoldModelDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> MoldModelName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FMoldModelDomain(
            const FMoldModelDomain& From
        );

        class GS2FORMATION_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Model::FMoldModel>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FMoldModelDomain> Self;
            const Request::FGetMoldModelRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FMoldModelDomain> Self,
                const Request::FGetMoldModelRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Model::FMoldModel>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetMoldModelRequestPtr Request
        );

        TSharedPtr<Gs2::Formation::Domain::Model::FFormModelDomain> FormModel(
            const FString FormModelName
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> MoldModelName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> MoldModelName
        );

        class GS2FORMATION_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Model::FMoldModel>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FMoldModelDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FMoldModelDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Model::FMoldModel>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FMoldModelDomain> FMoldModelDomainPtr;
}
