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

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

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

    class GS2STAMINA_API FRecoverIntervalTableMasterDomain:
        public TSharedFromThis<FRecoverIntervalTableMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Stamina::FGs2StaminaRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> RecoverIntervalTableName;
    private:

        FString ParentKey;

    public:

        FRecoverIntervalTableMasterDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> RecoverIntervalTableName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FRecoverIntervalTableMasterDomain(
            const FRecoverIntervalTableMasterDomain& From
        );

        class GS2STAMINA_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Model::FRecoverIntervalTableMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FRecoverIntervalTableMasterDomain> Self;
            const Request::FGetRecoverIntervalTableMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FRecoverIntervalTableMasterDomain> Self,
                const Request::FGetRecoverIntervalTableMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FRecoverIntervalTableMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetRecoverIntervalTableMasterRequestPtr Request
        );

        class GS2STAMINA_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FRecoverIntervalTableMasterDomain> Self;
            const Request::FUpdateRecoverIntervalTableMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FRecoverIntervalTableMasterDomain> Self,
                const Request::FUpdateRecoverIntervalTableMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateRecoverIntervalTableMasterRequestPtr Request
        );

        class GS2STAMINA_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FRecoverIntervalTableMasterDomain> Self;
            const Request::FDeleteRecoverIntervalTableMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FRecoverIntervalTableMasterDomain> Self,
                const Request::FDeleteRecoverIntervalTableMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteRecoverIntervalTableMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> RecoverIntervalTableName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> RecoverIntervalTableName
        );

        class GS2STAMINA_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Model::FRecoverIntervalTableMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FRecoverIntervalTableMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FRecoverIntervalTableMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FRecoverIntervalTableMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FRecoverIntervalTableMasterDomain> FRecoverIntervalTableMasterDomainPtr;
}
