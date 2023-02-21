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
#include "Distributor/Gs2Distributor.h"
#include "Distributor/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Distributor/Domain/Iterator/DescribeDistributorModelMastersIterator.h"
#include "Distributor/Domain/Iterator/DescribeDistributorModelsIterator.h"

namespace Gs2::Distributor::Domain::Model
{
    class FNamespaceDomain;
    class FDistributorModelMasterDomain;
    class FDistributorModelDomain;
    class FCurrentDistributorMasterDomain;
    class FDistributeDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FStampSheetResultDomain;
    class FStampSheetResultAccessTokenDomain;

    class GS2DISTRIBUTOR_API FDistributorModelMasterDomain:
        public TSharedFromThis<FDistributorModelMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Distributor::FGs2DistributorRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> DistributorName;
    private:

        FString ParentKey;

    public:

        FDistributorModelMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> DistributorName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FDistributorModelMasterDomain(
            const FDistributorModelMasterDomain& From
        );

        class GS2DISTRIBUTOR_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Model::FDistributorModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FDistributorModelMasterDomain> Self;
            const Request::FGetDistributorModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FDistributorModelMasterDomain> Self,
                const Request::FGetDistributorModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FDistributorModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetDistributorModelMasterRequestPtr Request
        );

        class GS2DISTRIBUTOR_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FDistributorModelMasterDomain> Self;
            const Request::FUpdateDistributorModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FDistributorModelMasterDomain> Self,
                const Request::FUpdateDistributorModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateDistributorModelMasterRequestPtr Request
        );

        class GS2DISTRIBUTOR_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FDistributorModelMasterDomain> Self;
            const Request::FDeleteDistributorModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FDistributorModelMasterDomain> Self,
                const Request::FDeleteDistributorModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteDistributorModelMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> DistributorName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> DistributorName
        );

        class GS2DISTRIBUTOR_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Model::FDistributorModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FDistributorModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FDistributorModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FDistributorModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FDistributorModelMasterDomain> FDistributorModelMasterDomainPtr;
}
