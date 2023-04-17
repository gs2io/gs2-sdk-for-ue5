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

    class GS2STAMINA_API FStaminaDomain:
        public TSharedFromThis<FStaminaDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Stamina::FGs2StaminaRestClientPtr Client;

        public:
        TOptional<int32> OverflowValue;
        TOptional<int32> GetOverflowValue() const
        {
            return OverflowValue;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> StaminaName;
    private:

        FString ParentKey;

    public:

        FStaminaDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> StaminaName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FStaminaDomain(
            const FStaminaDomain& From
        );

        class GS2STAMINA_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Model::FStamina>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FStaminaDomain> Self;
            const Request::FGetStaminaByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FStaminaDomain> Self,
                const Request::FGetStaminaByUserIdRequestPtr Request
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
            Request::FGetStaminaByUserIdRequestPtr Request
        );

        class GS2STAMINA_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FStaminaDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FStaminaDomain> Self;
            const Request::FUpdateStaminaByUserIdRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FStaminaDomain> Self,
                const Request::FUpdateStaminaByUserIdRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateStaminaByUserIdRequestPtr Request
        );

        class GS2STAMINA_API FConsumeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FStaminaDomain>,
            public TSharedFromThis<FConsumeTask>
        {
            const TSharedPtr<FStaminaDomain> Self;
            const Request::FConsumeStaminaByUserIdRequestPtr Request;
        public:
            explicit FConsumeTask(
                const TSharedPtr<FStaminaDomain> Self,
                const Request::FConsumeStaminaByUserIdRequestPtr Request
            );

            FConsumeTask(
                const FConsumeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
            ) override;
        };
        friend FConsumeTask;

        TSharedPtr<FAsyncTask<FConsumeTask>> Consume(
            Request::FConsumeStaminaByUserIdRequestPtr Request
        );

        class GS2STAMINA_API FRecoverTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FStaminaDomain>,
            public TSharedFromThis<FRecoverTask>
        {
            const TSharedPtr<FStaminaDomain> Self;
            const Request::FRecoverStaminaByUserIdRequestPtr Request;
        public:
            explicit FRecoverTask(
                const TSharedPtr<FStaminaDomain> Self,
                const Request::FRecoverStaminaByUserIdRequestPtr Request
            );

            FRecoverTask(
                const FRecoverTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
            ) override;
        };
        friend FRecoverTask;

        TSharedPtr<FAsyncTask<FRecoverTask>> Recover(
            Request::FRecoverStaminaByUserIdRequestPtr Request
        );

        class GS2STAMINA_API FRaiseMaxValueTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FStaminaDomain>,
            public TSharedFromThis<FRaiseMaxValueTask>
        {
            const TSharedPtr<FStaminaDomain> Self;
            const Request::FRaiseMaxValueByUserIdRequestPtr Request;
        public:
            explicit FRaiseMaxValueTask(
                const TSharedPtr<FStaminaDomain> Self,
                const Request::FRaiseMaxValueByUserIdRequestPtr Request
            );

            FRaiseMaxValueTask(
                const FRaiseMaxValueTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
            ) override;
        };
        friend FRaiseMaxValueTask;

        TSharedPtr<FAsyncTask<FRaiseMaxValueTask>> RaiseMaxValue(
            Request::FRaiseMaxValueByUserIdRequestPtr Request
        );

        class GS2STAMINA_API FSetMaxValueTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FStaminaDomain>,
            public TSharedFromThis<FSetMaxValueTask>
        {
            const TSharedPtr<FStaminaDomain> Self;
            const Request::FSetMaxValueByUserIdRequestPtr Request;
        public:
            explicit FSetMaxValueTask(
                const TSharedPtr<FStaminaDomain> Self,
                const Request::FSetMaxValueByUserIdRequestPtr Request
            );

            FSetMaxValueTask(
                const FSetMaxValueTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
            ) override;
        };
        friend FSetMaxValueTask;

        TSharedPtr<FAsyncTask<FSetMaxValueTask>> SetMaxValue(
            Request::FSetMaxValueByUserIdRequestPtr Request
        );

        class GS2STAMINA_API FSetRecoverIntervalTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FStaminaDomain>,
            public TSharedFromThis<FSetRecoverIntervalTask>
        {
            const TSharedPtr<FStaminaDomain> Self;
            const Request::FSetRecoverIntervalByUserIdRequestPtr Request;
        public:
            explicit FSetRecoverIntervalTask(
                const TSharedPtr<FStaminaDomain> Self,
                const Request::FSetRecoverIntervalByUserIdRequestPtr Request
            );

            FSetRecoverIntervalTask(
                const FSetRecoverIntervalTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
            ) override;
        };
        friend FSetRecoverIntervalTask;

        TSharedPtr<FAsyncTask<FSetRecoverIntervalTask>> SetRecoverInterval(
            Request::FSetRecoverIntervalByUserIdRequestPtr Request
        );

        class GS2STAMINA_API FSetRecoverValueTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FStaminaDomain>,
            public TSharedFromThis<FSetRecoverValueTask>
        {
            const TSharedPtr<FStaminaDomain> Self;
            const Request::FSetRecoverValueByUserIdRequestPtr Request;
        public:
            explicit FSetRecoverValueTask(
                const TSharedPtr<FStaminaDomain> Self,
                const Request::FSetRecoverValueByUserIdRequestPtr Request
            );

            FSetRecoverValueTask(
                const FSetRecoverValueTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
            ) override;
        };
        friend FSetRecoverValueTask;

        TSharedPtr<FAsyncTask<FSetRecoverValueTask>> SetRecoverValue(
            Request::FSetRecoverValueByUserIdRequestPtr Request
        );

        class GS2STAMINA_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Stamina::Domain::Model::FStaminaDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FStaminaDomain> Self;
            const Request::FDeleteStaminaByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FStaminaDomain> Self,
                const Request::FDeleteStaminaByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteStaminaByUserIdRequestPtr Request
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
            const TSharedPtr<FStaminaDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FStaminaDomain> Self
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

    };

    typedef TSharedPtr<FStaminaDomain> FStaminaDomainPtr;
}
