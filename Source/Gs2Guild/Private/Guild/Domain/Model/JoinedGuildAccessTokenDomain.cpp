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

#include "Guild/Domain/Model/JoinedGuildAccessToken.h"
#include "Guild/Domain/Model/JoinedGuild.h"
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
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Guild::Domain::Model
{

    FJoinedGuildAccessTokenDomain::FJoinedGuildAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> GuildModelName,
        const TOptional<FString> GuildName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        GuildModelName(GuildModelName),
        GuildName(GuildName),
        ParentKey(Gs2::Guild::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "JoinedGuild"
        ))
    {
    }

    FJoinedGuildAccessTokenDomain::FJoinedGuildAccessTokenDomain(
        const FJoinedGuildAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        GuildModelName(From.GuildModelName),
        GuildName(From.GuildName),
        ParentKey(From.ParentKey)
    {

    }

    FJoinedGuildAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FJoinedGuildAccessTokenDomain>& Self,
        const Request::FGetJoinedGuildRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FJoinedGuildAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FJoinedGuildAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FJoinedGuild>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->GetJoinedGuild(
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
                const auto ParentKey = Gs2::Guild::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "JoinedGuild"
                );
                const auto Key = Gs2::Guild::Domain::Model::FJoinedGuildDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGuildModelName(),
                    ResultModel->GetItem()->GetGuildName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FJoinedGuild::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FJoinedGuildAccessTokenDomain::FGetTask>> FJoinedGuildAccessTokenDomain::Get(
        Request::FGetJoinedGuildRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FJoinedGuildAccessTokenDomain::FWithdrawalTask::FWithdrawalTask(
        const TSharedPtr<FJoinedGuildAccessTokenDomain>& Self,
        const Request::FWithdrawalRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FJoinedGuildAccessTokenDomain::FWithdrawalTask::FWithdrawalTask(
        const FWithdrawalTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FJoinedGuildAccessTokenDomain::FWithdrawalTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FJoinedGuildAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->Withdrawal(
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
                const auto ParentKey = Gs2::Guild::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "JoinedGuild"
                );
                const auto Key = Gs2::Guild::Domain::Model::FJoinedGuildDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGuildModelName(),
                    ResultModel->GetItem()->GetGuildName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FJoinedGuild::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetGuild() != nullptr)
            {
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Guild"
                );
                const auto Key = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                    ResultModel->GetGuild()->GetGuildModelName(),
                    ResultModel->GetGuild()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FGuild::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetGuild(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FJoinedGuildAccessTokenDomain::FWithdrawalTask>> FJoinedGuildAccessTokenDomain::Withdrawal(
        Request::FWithdrawalRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FWithdrawalTask>>(this->AsShared(), Request);
    }

    FString FJoinedGuildAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> GuildModelName,
        TOptional<FString> GuildName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (GuildModelName.IsSet() ? *GuildModelName : "null") + ":" +
            (GuildName.IsSet() ? *GuildName : "null") + ":" +
            ChildType;
    }

    FString FJoinedGuildAccessTokenDomain::CreateCacheKey(
        TOptional<FString> GuildModelName,
        TOptional<FString> GuildName
    )
    {
        return FString("") +
            (GuildModelName.IsSet() ? *GuildModelName : "null") + ":" + 
            (GuildName.IsSet() ? *GuildName : "null");
    }

    FJoinedGuildAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FJoinedGuildAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FJoinedGuildAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FJoinedGuildAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FJoinedGuild>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Guild::Model::FJoinedGuild> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Guild::Model::FJoinedGuild>(
            Self->ParentKey,
            Gs2::Guild::Domain::Model::FJoinedGuildDomain::CreateCacheKey(
                Self->GuildModelName,
                Self->GuildName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Guild::Request::FGetJoinedGuildRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Guild::Domain::Model::FJoinedGuildDomain::CreateCacheKey(
                    Self->GuildModelName,
                    Self->GuildName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FJoinedGuild::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "joinedGuild")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Guild::Model::FJoinedGuild>(
                Self->ParentKey,
                Gs2::Guild::Domain::Model::FJoinedGuildDomain::CreateCacheKey(
                    Self->GuildModelName,
                    Self->GuildName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FJoinedGuildAccessTokenDomain::FModelTask>> FJoinedGuildAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FJoinedGuildAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FJoinedGuildAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FJoinedGuildPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FJoinedGuild::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FJoinedGuildDomain::CreateCacheKey(
                GuildModelName,
                GuildName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FJoinedGuild>(obj));
            }
        );
    }

    void FJoinedGuildAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Guild::Model::FJoinedGuild::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FJoinedGuildDomain::CreateCacheKey(
                GuildModelName,
                GuildName
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

