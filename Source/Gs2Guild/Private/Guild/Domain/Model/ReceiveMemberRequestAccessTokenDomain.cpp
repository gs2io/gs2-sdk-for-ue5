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

#include "Guild/Domain/Model/ReceiveMemberRequestAccessToken.h"
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
#include "Guild/Domain/Model/ReceiveMemberRequestAccessToken.h"
#include "Guild/Domain/Model/SendMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequestAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Guild::Domain::Model
{

    FReceiveMemberRequestAccessTokenDomain::FReceiveMemberRequestAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> GuildModelName,
        const TOptional<FString> FromUserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        GuildModelName(GuildModelName),
        FromUserId(FromUserId),
        ParentKey(Gs2::Guild::Domain::Model::FGuildAccessTokenDomain::CreateCacheParentKey(
            NamespaceName,
            GuildModelName,
            GuildName(),
            "ReceiveMemberRequest"
        ))
    {
    }

    FReceiveMemberRequestAccessTokenDomain::FReceiveMemberRequestAccessTokenDomain(
        const FReceiveMemberRequestAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        GuildModelName(From.GuildModelName),
        FromUserId(From.FromUserId),
        ParentKey(From.ParentKey)
    {

    }

    FString FReceiveMemberRequestAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> GuildModelName,
        TOptional<FString> GuildName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (GuildModelName.IsSet() ? *GuildModelName : "null") + ":" +
            (GuildName.IsSet() ? *GuildName : "null") + ":" +
            ChildType;
    }

    FString FReceiveMemberRequestAccessTokenDomain::CreateCacheKey(
        TOptional<FString> FromUserId
    )
    {
        return FString("") +
            (FromUserId.IsSet() ? *FromUserId : "null");
    }

    FReceiveMemberRequestAccessTokenDomain::FAcceptTask::FAcceptTask(
        const TSharedPtr<FReceiveMemberRequestAccessTokenDomain>& Self
    ): Self(Self)
    {

    }

    FReceiveMemberRequestAccessTokenDomain::FAcceptTask::FAcceptTask(
        const FAcceptTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveMemberRequestAccessTokenDomain::FAcceptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FReceiveMemberRequestAccessTokenDomain>> Result
    )
    {
        const auto Future = Self->Client->AcceptRequest(
            MakeShared<Gs2::Guild::Request::FAcceptRequestRequest>()
                ->WithContextStack(Self->Gs2->DefaultContextStack)
                ->WithNamespaceName(Self->NamespaceName)
                ->WithAccessToken(Self->AccessToken->GetToken())
                ->WithGuildModelName(Self->GuildModelName)
                ->WithFromUserId(Self->FromUserId)
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Guild::Domain::Model::FGuildAccessTokenDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->GuildModelName,
                    Self->GuildName(),
                    "ReceiveMemberRequest"
                );
                const auto Key = Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Gs2->Cache->Delete(Gs2::Guild::Model::FReceiveMemberRequest::TypeName, ParentKey, Key);
            }
            if (ResultModel->GetGuild() != nullptr)
            {
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Guild"
                );
                const auto Key = Gs2::Guild::Domain::Model::FGuildAccessTokenDomain::CreateCacheKey(
                    ResultModel->GetGuild()->GetGuildModelName(),
                    ResultModel->GetGuild()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Guild::Model::FGuild::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveMemberRequestAccessTokenDomain::FAcceptTask>> FReceiveMemberRequestAccessTokenDomain::Accept() {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveMemberRequestAccessTokenDomain::FAcceptTask>>(
            this->AsShared()
        );
    }

    FReceiveMemberRequestAccessTokenDomain::FRejectTask::FRejectTask(
        const TSharedPtr<FReceiveMemberRequestAccessTokenDomain>& Self
    ): Self(Self)
    {

    }

    FReceiveMemberRequestAccessTokenDomain::FRejectTask::FRejectTask(
        const FRejectTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveMemberRequestAccessTokenDomain::FRejectTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FReceiveMemberRequestAccessTokenDomain>> Result
    )
    {
        const auto Future = Self->Client->RejectRequest(
            MakeShared<Gs2::Guild::Request::FRejectRequestRequest>()
                ->WithContextStack(Self->Gs2->DefaultContextStack)
                ->WithNamespaceName(Self->NamespaceName)
                ->WithAccessToken(Self->AccessToken->GetToken())
                ->WithGuildModelName(Self->GuildModelName)
                ->WithFromUserId(Self->FromUserId)
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Guild::Domain::Model::FGuildAccessTokenDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->GuildModelName,
                    Self->GuildName(),
                    "ReceiveMemberRequest"
                );
                const auto Key = Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Gs2->Cache->Delete(Gs2::Guild::Model::FReceiveMemberRequest::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveMemberRequestAccessTokenDomain::FRejectTask>> FReceiveMemberRequestAccessTokenDomain::Reject() {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveMemberRequestAccessTokenDomain::FRejectTask>>(
            this->AsShared()
        );
    }
    
    FReceiveMemberRequestAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FReceiveMemberRequestAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FReceiveMemberRequestAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveMemberRequestAccessTokenDomain::FModelTask::Action(
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

    TSharedPtr<FAsyncTask<FReceiveMemberRequestAccessTokenDomain::FModelTask>> FReceiveMemberRequestAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveMemberRequestAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FReceiveMemberRequestAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FReceiveMemberRequestPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FReceiveMemberRequest::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain::CreateCacheKey(
                FromUserId
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FReceiveMemberRequest>(obj));
            }
        );
    }

    void FReceiveMemberRequestAccessTokenDomain::Unsubscribe(
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

