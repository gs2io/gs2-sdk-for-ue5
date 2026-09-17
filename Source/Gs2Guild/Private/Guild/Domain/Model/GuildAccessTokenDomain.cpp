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
#include "Guild/Domain/Model/LastGuildMasterActivity.h"
#include "Guild/Domain/Model/LastGuildMasterActivityAccessToken.h"
#include "Guild/Domain/Model/CurrentGuildMaster.h"
#include "Guild/Domain/Model/ReceiveMemberRequest.h"
#include "Guild/Domain/Model/ReceiveMemberRequestAccessToken.h"
#include "Guild/Domain/Model/SendMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequestAccessToken.h"
#include "Guild/Domain/Model/IgnoreUser.h"
#include "Guild/Domain/Model/IgnoreUserAccessToken.h"

#include "Guild/Model/Cache/IgnoreUser.h"
#include "Guild/Model/Cache/Guild.h"
#include "Guild/Model/Cache/ReceiveMemberRequest.h"
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
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> GuildName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        GuildModelName(GuildModelName),
        AccessToken(AccessToken),
        GuildNameValue(GuildName.IsSet() ? GuildName : AccessToken->GetUserId()),
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
        GuildNameValue(From.GuildNameValue),
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
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName())
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
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithGuildModelName(Self->GuildModelName);
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
                Gs2::Guild::Model::Cache::FGuildCache::Put(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    ResultModel->GetItem()->GetGuildModelName(),
                    ResultModel->GetItem()->GetName(),
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    ResultModel->GetItem()
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

    FGuildAccessTokenDomain::FBatchUpdateMemberRoleTask::FBatchUpdateMemberRoleTask(
        const TSharedPtr<FGuildAccessTokenDomain>& Self,
        const Request::FBatchUpdateMemberRoleRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildAccessTokenDomain::FBatchUpdateMemberRoleTask::FBatchUpdateMemberRoleTask(
        const FBatchUpdateMemberRoleTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildAccessTokenDomain::FBatchUpdateMemberRoleTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->BatchUpdateMemberRole(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetItem() != nullptr)
            {
                Gs2::Guild::Model::Cache::FGuildCache::Put(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    ResultModel->GetItem()->GetGuildModelName(),
                    ResultModel->GetItem()->GetName(),
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    ResultModel->GetItem()
                );
            }
        }
        auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGuildAccessTokenDomain::FBatchUpdateMemberRoleTask>> FGuildAccessTokenDomain::BatchUpdateMemberRole(
        Request::FBatchUpdateMemberRoleRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FBatchUpdateMemberRoleTask>>(this->AsShared(), Request);
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
            ->WithGuildName(Self->GuildName())
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

    FGuildAccessTokenDomain::FGetLastGuildMasterActivityTask::FGetLastGuildMasterActivityTask(
        const TSharedPtr<FGuildAccessTokenDomain>& Self,
        const Request::FGetLastGuildMasterActivityRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildAccessTokenDomain::FGetLastGuildMasterActivityTask::FGetLastGuildMasterActivityTask(
        const FGetLastGuildMasterActivityTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildAccessTokenDomain::FGetLastGuildMasterActivityTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FLastGuildMasterActivity>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->GetLastGuildMasterActivity(
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
                    "LastGuildMasterActivity"
                );
                const auto Key = Gs2::Guild::Domain::Model::FLastGuildMasterActivityDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FLastGuildMasterActivity::TypeName,
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
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGuildAccessTokenDomain::FGetLastGuildMasterActivityTask>> FGuildAccessTokenDomain::GetLastGuildMasterActivity(
        Request::FGetLastGuildMasterActivityRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetLastGuildMasterActivityTask>>(this->AsShared(), Request);
    }

    FGuildAccessTokenDomain::FPromoteSeniorMemberTask::FPromoteSeniorMemberTask(
        const TSharedPtr<FGuildAccessTokenDomain>& Self,
        const Request::FPromoteSeniorMemberRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildAccessTokenDomain::FPromoteSeniorMemberTask::FPromoteSeniorMemberTask(
        const FPromoteSeniorMemberTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildAccessTokenDomain::FPromoteSeniorMemberTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FLastGuildMasterActivityAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->PromoteSeniorMember(
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
                    "LastGuildMasterActivity"
                );
                const auto Key = Gs2::Guild::Domain::Model::FLastGuildMasterActivityDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FLastGuildMasterActivity::TypeName,
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
        auto Domain = MakeShared<Gs2::Guild::Domain::Model::FLastGuildMasterActivityAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Request->GetGuildModelName(),
            Self->AccessToken
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGuildAccessTokenDomain::FPromoteSeniorMemberTask>> FGuildAccessTokenDomain::PromoteSeniorMember(
        Request::FPromoteSeniorMemberRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPromoteSeniorMemberTask>>(this->AsShared(), Request);
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
            Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::CreateCacheParentKey(
                NamespaceName,
                GuildModelName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FGuildAccessTokenDomain::UnsubscribeReceiveRequests(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Guild::Model::FReceiveMemberRequest::TypeName,
            Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::CreateCacheParentKey(
                NamespaceName,
                GuildModelName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FGuildAccessTokenDomain::FCollectReceiveRequestsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Guild::Model::FReceiveMemberRequestPtr>>, public TSharedFromThis<FCollectReceiveRequestsTask>
    {
        const TSharedPtr<FGuildAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Guild::Model::FReceiveMemberRequestPtr>)> OnCollected;

    public:
        explicit FCollectReceiveRequestsTask(const TSharedPtr<FGuildAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FReceiveMemberRequestPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectReceiveRequestsTask(const FCollectReceiveRequestsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Guild::Model::FReceiveMemberRequestPtr>>> Result) override
        {
            TArray<Gs2::Guild::Model::FReceiveMemberRequestPtr> Items;
            auto Iterator = Self->ReceiveRequests()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Guild::Model::FReceiveMemberRequestPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FGuildAccessTokenDomain::SubscribeReceiveRequests(
        TFunction<void(TArray<Gs2::Guild::Model::FReceiveMemberRequestPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Guild::Domain::FGs2GuildDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryGuildModelName = GuildModelName;
                const auto Parent = Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::CreateCacheParentKey(
        NamespaceName,
        GuildModelName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Guild::Model::FReceiveMemberRequest::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Guild::Model::FReceiveMemberRequestPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Guild::Model::FReceiveMemberRequest>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryGuildModelName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FGuildAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryGuildModelName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectReceiveRequestsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FGuildAccessTokenDomain::InvalidateReceiveRequests()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Guild::Model::FReceiveMemberRequest::TypeName,
            Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::CreateCacheParentKey(
        NamespaceName,
        GuildModelName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FGuildAccessTokenDomain::FSubscribeReceiveRequestsWithInitialCallTask::FSubscribeReceiveRequestsWithInitialCallTask(const TSharedPtr<FGuildAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FReceiveMemberRequestPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FGuildAccessTokenDomain::FSubscribeReceiveRequestsWithInitialCallTask::FSubscribeReceiveRequestsWithInitialCallTask(const FSubscribeReceiveRequestsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FGuildAccessTokenDomain::FSubscribeReceiveRequestsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectReceiveRequestsTask>>(Self, TFunction<void(TArray<Gs2::Guild::Model::FReceiveMemberRequestPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeReceiveRequests(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FGuildAccessTokenDomain::FSubscribeReceiveRequestsWithInitialCallTask>> FGuildAccessTokenDomain::SubscribeReceiveRequestsWithInitialCall(TFunction<void(TArray<Gs2::Guild::Model::FReceiveMemberRequestPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeReceiveRequestsWithInitialCallTask>>(this->AsShared(), Callback);
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
            Gs2::Guild::Model::Cache::FIgnoreUserCache::CreateCacheParentKey(
                NamespaceName,
                GuildModelName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FGuildAccessTokenDomain::UnsubscribeIgnoreUsers(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Guild::Model::FIgnoreUser::TypeName,
            Gs2::Guild::Model::Cache::FIgnoreUserCache::CreateCacheParentKey(
                NamespaceName,
                GuildModelName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FGuildAccessTokenDomain::FCollectIgnoreUsersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Guild::Model::FIgnoreUserPtr>>, public TSharedFromThis<FCollectIgnoreUsersTask>
    {
        const TSharedPtr<FGuildAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Guild::Model::FIgnoreUserPtr>)> OnCollected;

    public:
        explicit FCollectIgnoreUsersTask(const TSharedPtr<FGuildAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FIgnoreUserPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectIgnoreUsersTask(const FCollectIgnoreUsersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Guild::Model::FIgnoreUserPtr>>> Result) override
        {
            TArray<Gs2::Guild::Model::FIgnoreUserPtr> Items;
            auto Iterator = Self->IgnoreUsers()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Guild::Model::FIgnoreUserPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FGuildAccessTokenDomain::SubscribeIgnoreUsers(
        TFunction<void(TArray<Gs2::Guild::Model::FIgnoreUserPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Guild::Domain::FGs2GuildDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryGuildModelName = GuildModelName;
                const auto Parent = Gs2::Guild::Model::Cache::FIgnoreUserCache::CreateCacheParentKey(
        NamespaceName,
        GuildModelName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Guild::Model::FIgnoreUser::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Guild::Model::FIgnoreUserPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Guild::Model::FIgnoreUser>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryGuildModelName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FGuildAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryGuildModelName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectIgnoreUsersTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FGuildAccessTokenDomain::InvalidateIgnoreUsers()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Guild::Model::FIgnoreUser::TypeName,
            Gs2::Guild::Model::Cache::FIgnoreUserCache::CreateCacheParentKey(
        NamespaceName,
        GuildModelName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FGuildAccessTokenDomain::FSubscribeIgnoreUsersWithInitialCallTask::FSubscribeIgnoreUsersWithInitialCallTask(const TSharedPtr<FGuildAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FIgnoreUserPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FGuildAccessTokenDomain::FSubscribeIgnoreUsersWithInitialCallTask::FSubscribeIgnoreUsersWithInitialCallTask(const FSubscribeIgnoreUsersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FGuildAccessTokenDomain::FSubscribeIgnoreUsersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectIgnoreUsersTask>>(Self, TFunction<void(TArray<Gs2::Guild::Model::FIgnoreUserPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeIgnoreUsers(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FGuildAccessTokenDomain::FSubscribeIgnoreUsersWithInitialCallTask>> FGuildAccessTokenDomain::SubscribeIgnoreUsersWithInitialCall(TFunction<void(TArray<Gs2::Guild::Model::FIgnoreUserPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeIgnoreUsersWithInitialCallTask>>(this->AsShared(), Callback);
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

    TSharedPtr<Gs2::Guild::Domain::Model::FLastGuildMasterActivityAccessTokenDomain> FGuildAccessTokenDomain::LastGuildMasterActivity(
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FLastGuildMasterActivityAccessTokenDomain>(
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
        const FString CacheKey = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
            Self->GuildModelName,
            Self->GuildName()
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Guild::Model::FGuild::TypeName,
            Self->ParentKey,
            CacheKey,
            [this, Result, CacheKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Guild::Model::FGuild> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Guild::Model::FGuild>(
                    Self->ParentKey,
                    CacheKey,
                    &Value
                );
                if (!bCacheHit) {
                    const auto Future = Self->Get(
                        MakeShared<Gs2::Guild::Request::FGetGuildRequest>()
                    );
                    Future->StartSynchronousTask();
                    if (Future->GetTask().IsError())
                    {
                        const auto Error = Future->GetTask().Error();
                        if (!Error.IsValid() || Error->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                        {
                            return Error;
                        }
                        Self->Gs2->Cache->Put(
                            Gs2::Guild::Model::FGuild::TypeName,
                            Self->ParentKey,
                            CacheKey,
                            nullptr,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );

                        if (!Error->GetErrors().IsValid() || Error->Count() == 0 || !Error->Detail(0).IsValid() || Error->Detail(0)->GetComponent() != "guild")
                        {
                            return Error;
                        }
                    }
                    else
                    {
                        Value = Future->GetTask().Result();
                    }
                    Future->EnsureCompletion();
                }
                if (!bCacheHit)
                {
                    FGs2ObjectPtr ExistingObject;
                    const bool Existing = Self->Gs2->Cache->TryGet(
                        Gs2::Guild::Model::FGuild::TypeName,
                        Self->ParentKey,
                        CacheKey,
                        &ExistingObject
                    );
                    if (!Existing || ExistingObject != Value)
                    {
                        Self->Gs2->Cache->Put(
                            Gs2::Guild::Model::FGuild::TypeName,
                            Self->ParentKey,
                            CacheKey,
                            Value,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
                }

                *Result = Value;

                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FGuildAccessTokenDomain::FModelTask>> FGuildAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FGuildAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FGuildAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FGuildPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Guild::Domain::FGs2GuildDomain> WeakService = Service;
        const FString RegisteredParentKey = ParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryGuildModelName = GuildModelName;
        const TOptional<FString> QueryGuildName = GuildName();
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FGuild::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                GuildModelName,
                GuildName()
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FGuild>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryGuildModelName, QueryGuildName, SourceToken, RegisteredUserId]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet())
                {
                    return;
                }
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId)
                {
                    return;
                }
                const auto Domain = MakeShared<FGuildAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryGuildModelName,
                    TokenSnapshot,
                    QueryGuildName
                );
                Domain->GuildNameValue = QueryGuildName;
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
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
                GuildName()
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

