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
#include "Stamina/Gs2Stamina.h"
#include "Stamina/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Stamina/Domain/Iterator/DescribeStaminaModelMastersIterator.h"
#include "Stamina/Domain/Iterator/DescribeMaxStaminaTableMastersIterator.h"
#include "Stamina/Domain/Iterator/DescribeRecoverIntervalTableMastersIterator.h"
#include "Stamina/Domain/Iterator/DescribeRecoverValueTableMastersIterator.h"
#include "Stamina/Domain/Iterator/DescribeStaminaModelsIterator.h"
#include "Stamina/Domain/Iterator/DescribeStaminasIterator.h"
#include "Stamina/Domain/Iterator/DescribeStaminasByUserIdIterator.h"

namespace Gs2::Stamina::Domain::Model
{
    class FNamespaceDomain;
    class FStaminaModelMasterDomain;
    class FMaxStaminaTableMasterDomain;
    class FRecoverIntervalTableMasterDomain;
    class FRecoverValueTableMasterDomain;
    class FCurrentStaminaMasterDomain;
    class FStaminaModelDomain;
    class FStaminaDomain;
    class FStaminaAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2STAMINA_API FMaxStaminaTableMasterDomain:
        public TSharedFromThis<FMaxStaminaTableMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Stamina::FGs2StaminaRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> MaxStaminaTableName;
    private:

        FString ParentKey;

    public:

        FMaxStaminaTableMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> MaxStaminaTableName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FMaxStaminaTableMasterDomain(
            const FMaxStaminaTableMasterDomain& From
        );

        class GS2STAMINA_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Model::FMaxStaminaTableMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FMaxStaminaTableMasterDomain> Self;
            const Request::FGetMaxStaminaTableMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FMaxStaminaTableMasterDomain> Self,
                const Request::FGetMaxStaminaTableMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FMaxStaminaTableMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetMaxStaminaTableMasterRequestPtr Request
        );

        class GS2STAMINA_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FMaxStaminaTableMasterDomain> Self;
            const Request::FUpdateMaxStaminaTableMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FMaxStaminaTableMasterDomain> Self,
                const Request::FUpdateMaxStaminaTableMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateMaxStaminaTableMasterRequestPtr Request
        );

        class GS2STAMINA_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FMaxStaminaTableMasterDomain> Self;
            const Request::FDeleteMaxStaminaTableMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FMaxStaminaTableMasterDomain> Self,
                const Request::FDeleteMaxStaminaTableMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteMaxStaminaTableMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> MaxStaminaTableName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> MaxStaminaTableName
        );

        class GS2STAMINA_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Model::FMaxStaminaTableMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FMaxStaminaTableMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FMaxStaminaTableMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FMaxStaminaTableMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FMaxStaminaTableMasterDomain> FMaxStaminaTableMasterDomainPtr;
}
