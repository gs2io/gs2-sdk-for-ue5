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

#include "Guild/Domain/Model/RoleModel.h"
#include "Guild/Domain/Model/Namespace.h"
#include "Guild/Domain/Model/GuildModelMaster.h"
#include "Guild/Domain/Model/GuildModel.h"
#include "Guild/Domain/Model/User.h"
#include "Guild/Domain/Model/UserAccessToken.h"
#include "Guild/Domain/Model/Guild.h"
#include "Guild/Domain/Model/JoinedGuild.h"
#include "Guild/Domain/Model/JoinedGuildAccessToken.h"
#include "Guild/Domain/Model/CurrentGuildMaster.h"
#include "Guild/Domain/Model/ReceiveMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequestAccessToken.h"
#include "Guild/Domain/Model/IgnoreUser.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Guild::Domain::Model
{

    FRoleModelDomain::FRoleModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> GuildModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        GuildModelName(GuildModelName),
        ParentKey(Gs2::Guild::Domain::Model::FGuildModelDomain::CreateCacheParentKey(
            NamespaceName,
            GuildModelName,
            "RoleModel"
        ))
    {
    }

    FRoleModelDomain::FRoleModelDomain(
        const FRoleModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        GuildModelName(From.GuildModelName),
        ParentKey(From.ParentKey)
    {

    }

    FString FRoleModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> GuildModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (GuildModelName.IsSet() ? *GuildModelName : "null") + ":" +
            ChildType;
    }

    FString FRoleModelDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FRoleModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FRoleModelDomain> Self
    ): Self(Self)
    {

    }

    FRoleModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRoleModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FRoleModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Guild::Model::FRoleModel> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Guild::Model::FRoleModel>(
            Self->ParentKey,
            Gs2::Guild::Domain::Model::FRoleModelDomain::CreateCacheKey(
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoleModelDomain::FModelTask>> FRoleModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRoleModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FRoleModelDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FRoleModelPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FRoleModel::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FRoleModelDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FRoleModel>(obj));
            }
        );
    }

    void FRoleModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Guild::Model::FRoleModel::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FRoleModelDomain::CreateCacheKey(
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

