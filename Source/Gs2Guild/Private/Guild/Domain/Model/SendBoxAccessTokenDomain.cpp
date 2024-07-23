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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Guild/Domain/Model/SendBoxAccessToken.h"
#include "Guild/Domain/Model/SendBox.h"
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
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Guild::Domain::Model
{

    FSendBoxAccessTokenDomain::FSendBoxAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> GuildModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        GuildModelName(GuildModelName),
        ParentKey(Gs2::Guild::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "SendBox"
        ))
    {
    }

    FSendBoxAccessTokenDomain::FSendBoxAccessTokenDomain(
        const FSendBoxAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        GuildModelName(From.GuildModelName),
        ParentKey(From.ParentKey)
    {

    }

    FString FSendBoxAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> GuildModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (GuildModelName.IsSet() ? *GuildModelName : "null") + ":" +
            ChildType;
    }

    FString FSendBoxAccessTokenDomain::CreateCacheKey(
        TOptional<FString> GuildModelName
    )
    {
        return FString("") +
            (GuildModelName.IsSet() ? *GuildModelName : "null");
    }

    FSendBoxAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FSendBoxAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FSendBoxAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSendBoxAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FSendBox>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Guild::Model::FSendBox> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Guild::Model::FSendBox>(
            Self->ParentKey,
            Gs2::Guild::Domain::Model::FSendBoxDomain::CreateCacheKey(
                Self->GuildModelName
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSendBoxAccessTokenDomain::FModelTask>> FSendBoxAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSendBoxAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FSendBoxAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FSendBoxPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FSendBox::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FSendBoxDomain::CreateCacheKey(
                GuildModelName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FSendBox>(obj));
            }
        );
    }

    void FSendBoxAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Guild::Model::FSendBox::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FSendBoxDomain::CreateCacheKey(
                GuildModelName
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

