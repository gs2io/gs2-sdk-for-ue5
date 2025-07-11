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

#include "Guild/Domain/Model/ReceiveMemberRequest.h"
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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Guild::Domain::Model
{

    FReceiveMemberRequestDomain::FReceiveMemberRequestDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> GuildModelName,
        const TOptional<FString> GuildName,
        const TOptional<FString> FromUserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        GuildModelName(GuildModelName),
        GuildName(GuildName),
        FromUserId(FromUserId),
        ParentKey(Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheParentKey(
            NamespaceName,
            GuildModelName,
            GuildName,
            "ReceiveMemberRequest"
        ))
    {
    }

    FReceiveMemberRequestDomain::FReceiveMemberRequestDomain(
        const FReceiveMemberRequestDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        GuildModelName(From.GuildModelName),
        GuildName(From.GuildName),
        FromUserId(From.FromUserId),
        ParentKey(From.ParentKey)
    {

    }

    FReceiveMemberRequestDomain::FGetReceiveRequestByGuildNameTask::FGetReceiveRequestByGuildNameTask(
        const TSharedPtr<FReceiveMemberRequestDomain>& Self,
        const Request::FGetReceiveRequestByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceiveMemberRequestDomain::FGetReceiveRequestByGuildNameTask::FGetReceiveRequestByGuildNameTask(
        const FGetReceiveRequestByGuildNameTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveMemberRequestDomain::FGetReceiveRequestByGuildNameTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName)
            ->WithFromUserId(Self->FromUserId);
        const auto Future = Self->Client->GetReceiveRequestByGuildName(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->GuildModelName,
                    Self->GuildName,
                    "ReceiveMemberRequest"
                );
                const auto Key = Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FReceiveMemberRequest::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveMemberRequestDomain::FGetReceiveRequestByGuildNameTask>> FReceiveMemberRequestDomain::GetReceiveRequestByGuildName(
        Request::FGetReceiveRequestByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetReceiveRequestByGuildNameTask>>(this->AsShared(), Request);
    }

    FString FReceiveMemberRequestDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> GuildModelName,
        TOptional<FString> GuildName,
        TOptional<FString> TargetGuildName,
        TOptional<FString> FromUserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (GuildModelName.IsSet() ? *GuildModelName : "null") + ":" +
            (GuildName.IsSet() ? *GuildName : "null") + ":" +
            (TargetGuildName.IsSet() ? *TargetGuildName : "null") + ":" +
            (FromUserId.IsSet() ? *FromUserId : "null") + ":" +
            ChildType;
    }

    FString FReceiveMemberRequestDomain::CreateCacheKey(
        TOptional<FString> FromUserId
    )
    {
        return FString("") +
            (FromUserId.IsSet() ? *FromUserId : "null");
    }

    FReceiveMemberRequestDomain::FModelTask::FModelTask(
        const TSharedPtr<FReceiveMemberRequestDomain> Self
    ): Self(Self)
    {

    }

    FReceiveMemberRequestDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveMemberRequestDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FReceiveMemberRequest>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Guild::Model::FReceiveMemberRequest> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Guild::Model::FReceiveMemberRequest>(
            Self->ParentKey,
            Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain::CreateCacheKey(
                Self->FromUserId
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveMemberRequestDomain::FModelTask>> FReceiveMemberRequestDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveMemberRequestDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FReceiveMemberRequestDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FReceiveMemberRequestPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FReceiveMemberRequest::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain::CreateCacheKey(
                FromUserId
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FReceiveMemberRequest>(obj));
            }
        );
    }

    void FReceiveMemberRequestDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Guild::Model::FReceiveMemberRequest::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain::CreateCacheKey(
                FromUserId
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

