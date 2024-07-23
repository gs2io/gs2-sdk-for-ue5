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

#include "Guild/Domain/Model/GuildAccessToken.h"
#include "Guild/Domain/Model/Guild.h"
#include "Guild/Domain/Model/Namespace.h"
#include "Guild/Domain/Model/GuildModelMaster.h"
#include "Guild/Domain/Model/GuildModel.h"
#include "Guild/Domain/Model/User.h"
#include "Guild/Domain/Model/Guild.h"
#include "Guild/Domain/Model/GuildAccessToken.h"
#include "Guild/Domain/Model/JoinedGuild.h"
#include "Guild/Domain/Model/JoinedGuildAccessToken.h"
#include "Guild/Domain/Model/CurrentGuildMaster.h"
#include "Guild/Domain/Model/ReceiveMemberRequest.h"
#include "Guild/Domain/Model/ReceiveMemberRequestAccessToken.h"
#include "Guild/Domain/Model/SendMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequestAccessToken.h"
#include "Guild/Domain/Model/IgnoreUser.h"
#include "Guild/Domain/Model/IgnoreUserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Guild::Domain::Model
{

    FGuildAccessTokenDomain::FGuildAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> GuildModelName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        GuildModelName(GuildModelName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "Guild"
        ))
    {
    }

    FGuildAccessTokenDomain::FGuildAccessTokenDomain(
        const FGuildAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        GuildModelName(From.GuildModelName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FGuildAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FGuildAccessTokenDomain>& Self,
        const Request::FGetGuildRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FGuild>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->GetGuild(
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
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Guild"
                );
                const auto Key = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGuildModelName(),
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FGuild::TypeName,
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

    TSharedPtr<FAsyncTask<FGuildAccessTokenDomain::FGetTask>> FGuildAccessTokenDomain::Get(
        Request::FGetGuildRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FGuildAccessTokenDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FGuildAccessTokenDomain>& Self,
        const Request::FUpdateGuildRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildAccessTokenDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildAccessTokenDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->UpdateGuild(
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
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Guild"
                );
                const auto Key = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGuildModelName(),
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FGuild::TypeName,
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

    TSharedPtr<FAsyncTask<FGuildAccessTokenDomain::FUpdateTask>> FGuildAccessTokenDomain::Update(
        Request::FUpdateGuildRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FGuildAccessTokenDomain::FDeleteMemberTask::FDeleteMemberTask(
        const TSharedPtr<FGuildAccessTokenDomain>& Self,
        const Request::FDeleteMemberRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildAccessTokenDomain::FDeleteMemberTask::FDeleteMemberTask(
        const FDeleteMemberTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildAccessTokenDomain::FDeleteMemberTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->DeleteMember(
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
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Guild"
                );
                const auto Key = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGuildModelName(),
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Guild::Model::FGuild::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGuildAccessTokenDomain::FDeleteMemberTask>> FGuildAccessTokenDomain::DeleteMember(
        Request::FDeleteMemberRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteMemberTask>>(this->AsShared(), Request);
    }

    FGuildAccessTokenDomain::FUpdateMemberRoleTask::FUpdateMemberRoleTask(
        const TSharedPtr<FGuildAccessTokenDomain>& Self,
        const Request::FUpdateMemberRoleRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildAccessTokenDomain::FUpdateMemberRoleTask::FUpdateMemberRoleTask(
        const FUpdateMemberRoleTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildAccessTokenDomain::FUpdateMemberRoleTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->UpdateMemberRole(
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
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Guild"
                );
                const auto Key = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGuildModelName(),
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FGuild::TypeName,
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

    TSharedPtr<FAsyncTask<FGuildAccessTokenDomain::FUpdateMemberRoleTask>> FGuildAccessTokenDomain::UpdateMemberRole(
        Request::FUpdateMemberRoleRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateMemberRoleTask>>(this->AsShared(), Request);
    }

    FGuildAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FGuildAccessTokenDomain>& Self,
        const Request::FDeleteGuildRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->DeleteGuild(
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
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Guild"
                );
                const auto Key = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGuildModelName(),
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Guild::Model::FGuild::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGuildAccessTokenDomain::FDeleteTask>> FGuildAccessTokenDomain::Delete(
        Request::FDeleteGuildRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FGuildAccessTokenDomain::FVerifyIncludeMemberTask::FVerifyIncludeMemberTask(
        const TSharedPtr<FGuildAccessTokenDomain>& Self,
        const Request::FVerifyIncludeMemberRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildAccessTokenDomain::FVerifyIncludeMemberTask::FVerifyIncludeMemberTask(
        const FVerifyIncludeMemberTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildAccessTokenDomain::FVerifyIncludeMemberTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->VerifyIncludeMember(
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
            
        }
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGuildAccessTokenDomain::FVerifyIncludeMemberTask>> FGuildAccessTokenDomain::VerifyIncludeMember(
        Request::FVerifyIncludeMemberRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyIncludeMemberTask>>(this->AsShared(), Request);
    }

    FGuildAccessTokenDomain::FAddIgnoreUserTask::FAddIgnoreUserTask(
        const TSharedPtr<FGuildAccessTokenDomain>& Self,
        const Request::FAddIgnoreUserRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildAccessTokenDomain::FAddIgnoreUserTask::FAddIgnoreUserTask(
        const FAddIgnoreUserTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildAccessTokenDomain::FAddIgnoreUserTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FIgnoreUserAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->AddIgnoreUser(
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
                    Self->AccessToken->GetUserId(),
                    "IgnoreUser"
                );
                const auto Key = Gs2::Guild::Domain::Model::FIgnoreUserDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FIgnoreUser::TypeName,
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
        auto Domain = MakeShared<Gs2::Guild::Domain::Model::FIgnoreUserAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Request->GetGuildModelName(),
            Self->AccessToken
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGuildAccessTokenDomain::FAddIgnoreUserTask>> FGuildAccessTokenDomain::AddIgnoreUser(
        Request::FAddIgnoreUserRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAddIgnoreUserTask>>(this->AsShared(), Request);
    }

    Gs2::Guild::Domain::Iterator::FDescribeReceiveRequestsIteratorPtr FGuildAccessTokenDomain::ReceiveRequests(
    ) const
    {
        return MakeShared<Gs2::Guild::Domain::Iterator::FDescribeReceiveRequestsIterator>(
            Gs2,
            Client,
            NamespaceName,
            GuildModelName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FGuildAccessTokenDomain::SubscribeReceiveRequests(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Guild::Model::FReceiveMemberRequest::TypeName,
            Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheParentKey(
                NamespaceName,
                GuildModelName,
                AccessToken->GetUserId(),
                "ReceiveMemberRequest"
            ),
            Callback
        );
    }

    void FGuildAccessTokenDomain::UnsubscribeReceiveRequests(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Guild::Model::FReceiveMemberRequest::TypeName,
            Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheParentKey(
                NamespaceName,
                GuildModelName,
                AccessToken->GetUserId(),
                "ReceiveMemberRequest"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Guild::Domain::Model::FReceiveMemberRequestAccessTokenDomain> FGuildAccessTokenDomain::ReceiveMemberRequest(
        const FString FromUserId
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FReceiveMemberRequestAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            GuildModelName,
            AccessToken,
            FromUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(FromUserId)
        );
    }

    Gs2::Guild::Domain::Iterator::FDescribeIgnoreUsersIteratorPtr FGuildAccessTokenDomain::IgnoreUsers(
    ) const
    {
        return MakeShared<Gs2::Guild::Domain::Iterator::FDescribeIgnoreUsersIterator>(
            Gs2,
            Client,
            NamespaceName,
            GuildModelName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FGuildAccessTokenDomain::SubscribeIgnoreUsers(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Guild::Model::FIgnoreUser::TypeName,
            Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheParentKey(
                NamespaceName,
                GuildModelName,
                AccessToken->GetUserId(),
                "IgnoreUser"
            ),
            Callback
        );
    }

    void FGuildAccessTokenDomain::UnsubscribeIgnoreUsers(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Guild::Model::FIgnoreUser::TypeName,
            Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheParentKey(
                NamespaceName,
                GuildModelName,
                AccessToken->GetUserId(),
                "IgnoreUser"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Guild::Domain::Model::FIgnoreUserAccessTokenDomain> FGuildAccessTokenDomain::IgnoreUser(
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FIgnoreUserAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            GuildModelName,
            AccessToken
        );
    }

    FString FGuildAccessTokenDomain::CreateCacheParentKey(
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

    FString FGuildAccessTokenDomain::CreateCacheKey(
        TOptional<FString> GuildModelName,
        TOptional<FString> GuildName
    )
    {
        return FString("") +
            (GuildModelName.IsSet() ? *GuildModelName : "null") + ":" + 
            (GuildName.IsSet() ? *GuildName : "null");
    }

    FGuildAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FGuildAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FGuildAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FGuild>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Guild::Model::FGuild> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Guild::Model::FGuild>(
            Self->ParentKey,
            Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                Self->GuildModelName,
                Self->AccessToken->GetUserId()
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Guild::Request::FGetGuildRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                    Self->GuildModelName,
                    Self->AccessToken->GetUserId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FGuild::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "guild")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Guild::Model::FGuild>(
                Self->ParentKey,
                Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                    Self->GuildModelName,
                    Self->AccessToken->GetUserId()
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGuildAccessTokenDomain::FModelTask>> FGuildAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FGuildAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FGuildAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FGuildPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FGuild::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                GuildModelName,
                AccessToken->GetUserId()
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FGuild>(obj));
            }
        );
    }

    void FGuildAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Guild::Model::FGuild::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                GuildModelName,
                AccessToken->GetUserId()
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

