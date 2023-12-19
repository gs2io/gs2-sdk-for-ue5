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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Stamina/Domain/Model/RecoverIntervalTable.h"
#include "Stamina/Domain/Model/Namespace.h"
#include "Stamina/Domain/Model/StaminaModelMaster.h"
#include "Stamina/Domain/Model/MaxStaminaTableMaster.h"
#include "Stamina/Domain/Model/RecoverIntervalTableMaster.h"
#include "Stamina/Domain/Model/RecoverValueTableMaster.h"
#include "Stamina/Domain/Model/CurrentStaminaMaster.h"
#include "Stamina/Domain/Model/StaminaModel.h"
#include "Stamina/Domain/Model/Stamina.h"
#include "Stamina/Domain/Model/StaminaAccessToken.h"
#include "Stamina/Domain/Model/User.h"
#include "Stamina/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Stamina::Domain::Model
{

    FRecoverIntervalTableDomain::FRecoverIntervalTableDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Stamina::Domain::FGs2StaminaDomainPtr& Service
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Stamina::FGs2StaminaRestClient>(Gs2->RestSession)),
        ParentKey("stamina:RecoverIntervalTable")
    {
    }

    FRecoverIntervalTableDomain::FRecoverIntervalTableDomain(
        const FRecoverIntervalTableDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FString FRecoverIntervalTableDomain::CreateCacheParentKey(
        FString ChildType
    )
    {
        return FString("") +
            ChildType;
    }

    FString FRecoverIntervalTableDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FRecoverIntervalTableDomain::FModelTask::FModelTask(
        const TSharedPtr<FRecoverIntervalTableDomain> Self
    ): Self(Self)
    {

    }

    FRecoverIntervalTableDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverIntervalTableDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FRecoverIntervalTable>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Stamina::Model::FRecoverIntervalTable> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Stamina::Model::FRecoverIntervalTable>(
            Self->ParentKey,
            Gs2::Stamina::Domain::Model::FRecoverIntervalTableDomain::CreateCacheKey(
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRecoverIntervalTableDomain::FModelTask>> FRecoverIntervalTableDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRecoverIntervalTableDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FRecoverIntervalTableDomain::Subscribe(
        TFunction<void(Gs2::Stamina::Model::FRecoverIntervalTablePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Stamina::Model::FRecoverIntervalTable::TypeName,
            ParentKey,
            Gs2::Stamina::Domain::Model::FRecoverIntervalTableDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Stamina::Model::FRecoverIntervalTable>(obj));
            }
        );
    }

    void FRecoverIntervalTableDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Stamina::Model::FRecoverIntervalTable::TypeName,
            ParentKey,
            Gs2::Stamina::Domain::Model::FRecoverIntervalTableDomain::CreateCacheKey(
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

