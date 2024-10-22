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

#include "Account/Domain/Model/BanStatus.h"
#include "Account/Domain/Model/Namespace.h"
#include "Account/Domain/Model/Account.h"
#include "Account/Domain/Model/AccountAccessToken.h"
#include "Account/Domain/Model/TakeOver.h"
#include "Account/Domain/Model/TakeOverAccessToken.h"
#include "Account/Domain/Model/PlatformId.h"
#include "Account/Domain/Model/PlatformIdAccessToken.h"
#include "Account/Domain/Model/DataOwner.h"
#include "Account/Domain/Model/DataOwnerAccessToken.h"
#include "Account/Domain/Model/TakeOverTypeModel.h"
#include "Account/Domain/Model/TakeOverTypeModelMaster.h"
#include "Account/Domain/Model/CurrentModelMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Account::Domain::Model
{

    FBanStatusDomain::FBanStatusDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Account::Domain::FGs2AccountDomainPtr& Service,
        const TOptional<FString> Name
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Account::FGs2AccountRestClient>(Gs2->RestSession)),
        Name(Name),
        ParentKey("account:BanStatus")
    {
    }

    FBanStatusDomain::FBanStatusDomain(
        const FBanStatusDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        Name(From.Name),
        ParentKey(From.ParentKey)
    {

    }

    FString FBanStatusDomain::CreateCacheParentKey(
        TOptional<FString> Name,
        FString ChildType
    )
    {
        return FString("") +
            (Name.IsSet() ? *Name : "null") + ":" +
            ChildType;
    }

    FString FBanStatusDomain::CreateCacheKey(
        TOptional<FString> Name
    )
    {
        return FString("") +
            (Name.IsSet() ? *Name : "null");
    }

    FBanStatusDomain::FModelTask::FModelTask(
        const TSharedPtr<FBanStatusDomain> Self
    ): Self(Self)
    {

    }

    FBanStatusDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FBanStatusDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FBanStatus>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Account::Model::FBanStatus> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Account::Model::FBanStatus>(
            Self->ParentKey,
            Gs2::Account::Domain::Model::FBanStatusDomain::CreateCacheKey(
                Self->Name
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBanStatusDomain::FModelTask>> FBanStatusDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FBanStatusDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FBanStatusDomain::Subscribe(
        TFunction<void(Gs2::Account::Model::FBanStatusPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Account::Model::FBanStatus::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FBanStatusDomain::CreateCacheKey(
                Name
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Account::Model::FBanStatus>(obj));
            }
        );
    }

    void FBanStatusDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Account::Model::FBanStatus::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FBanStatusDomain::CreateCacheKey(
                Name
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

