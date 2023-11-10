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

namespace Gs2::Stamina::Domain
{
    class FGs2StaminaDomain;
    typedef TSharedPtr<FGs2StaminaDomain> FGs2StaminaDomainPtr;
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

    class GS2STAMINA_API FStaminaAccessTokenDomain:
        public TSharedFromThis<FStaminaAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Stamina::Domain::FGs2StaminaDomainPtr Service;
        const Gs2::Stamina::FGs2StaminaRestClientPtr Client;

        public:
        TOptional<int32> OverflowValue;
        TOptional<int32> GetOverflowValue() const
        {
            return OverflowValue;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> StaminaName;
    private:

        FString ParentKey;

    public:

        FStaminaAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Stamina::Domain::FGs2StaminaDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> StaminaName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FStaminaAccessTokenDomain(
            const FStaminaAccessTokenDomain& From
        );

        class GS2STAMINA_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Model::FStamina>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FStaminaAccessTokenDomain> Self;
            const Request::FGetStaminaRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FStaminaAccessTokenDomain>& Self,
                const Request::FGetStaminaRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FStamina>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetStaminaRequestPtr Request
        );

        class GS2STAMINA_API FConsumeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>,
            public TSharedFromThis<FConsumeTask>
        {
            const TSharedPtr<FStaminaAccessTokenDomain> Self;
            const Request::FConsumeStaminaRequestPtr Request;
        public:
            explicit FConsumeTask(
                const TSharedPtr<FStaminaAccessTokenDomain>& Self,
                const Request::FConsumeStaminaRequestPtr Request
            );

            FConsumeTask(
                const FConsumeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
            ) override;
        };
        friend FConsumeTask;

        TSharedPtr<FAsyncTask<FConsumeTask>> Consume(
            Request::FConsumeStaminaRequestPtr Request
        );

        class GS2STAMINA_API FSetMaxValueByStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>,
            public TSharedFromThis<FSetMaxValueByStatusTask>
        {
            const TSharedPtr<FStaminaAccessTokenDomain> Self;
            const Request::FSetMaxValueByStatusRequestPtr Request;
        public:
            explicit FSetMaxValueByStatusTask(
                const TSharedPtr<FStaminaAccessTokenDomain>& Self,
                const Request::FSetMaxValueByStatusRequestPtr Request
            );

            FSetMaxValueByStatusTask(
                const FSetMaxValueByStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
            ) override;
        };
        friend FSetMaxValueByStatusTask;

        TSharedPtr<FAsyncTask<FSetMaxValueByStatusTask>> SetMaxValueByStatus(
            Request::FSetMaxValueByStatusRequestPtr Request
        );

        class GS2STAMINA_API FSetRecoverIntervalByStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>,
            public TSharedFromThis<FSetRecoverIntervalByStatusTask>
        {
            const TSharedPtr<FStaminaAccessTokenDomain> Self;
            const Request::FSetRecoverIntervalByStatusRequestPtr Request;
        public:
            explicit FSetRecoverIntervalByStatusTask(
                const TSharedPtr<FStaminaAccessTokenDomain>& Self,
                const Request::FSetRecoverIntervalByStatusRequestPtr Request
            );

            FSetRecoverIntervalByStatusTask(
                const FSetRecoverIntervalByStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
            ) override;
        };
        friend FSetRecoverIntervalByStatusTask;

        TSharedPtr<FAsyncTask<FSetRecoverIntervalByStatusTask>> SetRecoverIntervalByStatus(
            Request::FSetRecoverIntervalByStatusRequestPtr Request
        );

        class GS2STAMINA_API FSetRecoverValueByStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>,
            public TSharedFromThis<FSetRecoverValueByStatusTask>
        {
            const TSharedPtr<FStaminaAccessTokenDomain> Self;
            const Request::FSetRecoverValueByStatusRequestPtr Request;
        public:
            explicit FSetRecoverValueByStatusTask(
                const TSharedPtr<FStaminaAccessTokenDomain>& Self,
                const Request::FSetRecoverValueByStatusRequestPtr Request
            );

            FSetRecoverValueByStatusTask(
                const FSetRecoverValueByStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
            ) override;
        };
        friend FSetRecoverValueByStatusTask;

        TSharedPtr<FAsyncTask<FSetRecoverValueByStatusTask>> SetRecoverValueByStatus(
            Request::FSetRecoverValueByStatusRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> StaminaName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> StaminaName
        );

        class GS2STAMINA_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Model::FStamina>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FStaminaAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FStaminaAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FStamina>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Stamina::Model::FStaminaPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FStaminaAccessTokenDomain> FStaminaAccessTokenDomainPtr;
}
