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

#include "Guild/Domain/Model/Guild.h"
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

    FGuildDomain::FGuildDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> GuildModelName,
        const TOptional<FString> GuildName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        GuildModelName(GuildModelName),
        GuildName(GuildName),
        ParentKey(Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "Guild"
        ))
    {
    }

    FGuildDomain::FGuildDomain(
        const FGuildDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        GuildModelName(From.GuildModelName),
        GuildName(From.GuildName),
        ParentKey(From.ParentKey)
    {

    }

    FGuildDomain::FGetTask::FGetTask(
        const TSharedPtr<FGuildDomain>& Self,
        const Request::FGetGuildRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FGuild>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
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

    TSharedPtr<FAsyncTask<FGuildDomain::FGetTask>> FGuildDomain::Get(
        Request::FGetGuildRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FGuildDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FGuildDomain>& Self,
        const Request::FUpdateGuildByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->UpdateGuildByGuildName(
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

    TSharedPtr<FAsyncTask<FGuildDomain::FUpdateTask>> FGuildDomain::Update(
        Request::FUpdateGuildByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FGuildDomain::FDeleteMemberTask::FDeleteMemberTask(
        const TSharedPtr<FGuildDomain>& Self,
        const Request::FDeleteMemberByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildDomain::FDeleteMemberTask::FDeleteMemberTask(
        const FDeleteMemberTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildDomain::FDeleteMemberTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->DeleteMemberByGuildName(
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

    TSharedPtr<FAsyncTask<FGuildDomain::FDeleteMemberTask>> FGuildDomain::DeleteMember(
        Request::FDeleteMemberByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteMemberTask>>(this->AsShared(), Request);
    }

    FGuildDomain::FUpdateMemberRoleTask::FUpdateMemberRoleTask(
        const TSharedPtr<FGuildDomain>& Self,
        const Request::FUpdateMemberRoleByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildDomain::FUpdateMemberRoleTask::FUpdateMemberRoleTask(
        const FUpdateMemberRoleTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildDomain::FUpdateMemberRoleTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->UpdateMemberRoleByGuildName(
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

    TSharedPtr<FAsyncTask<FGuildDomain::FUpdateMemberRoleTask>> FGuildDomain::UpdateMemberRole(
        Request::FUpdateMemberRoleByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateMemberRoleTask>>(this->AsShared(), Request);
    }

    FGuildDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FGuildDomain>& Self,
        const Request::FDeleteGuildByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->DeleteGuildByGuildName(
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

    TSharedPtr<FAsyncTask<FGuildDomain::FDeleteTask>> FGuildDomain::Delete(
        Request::FDeleteGuildByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FGuildDomain::FIncreaseMaximumCurrentMaximumMemberCountTask::FIncreaseMaximumCurrentMaximumMemberCountTask(
        const TSharedPtr<FGuildDomain>& Self,
        const Request::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildDomain::FIncreaseMaximumCurrentMaximumMemberCountTask::FIncreaseMaximumCurrentMaximumMemberCountTask(
        const FIncreaseMaximumCurrentMaximumMemberCountTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildDomain::FIncreaseMaximumCurrentMaximumMemberCountTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->IncreaseMaximumCurrentMaximumMemberCountByGuildName(
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

    TSharedPtr<FAsyncTask<FGuildDomain::FIncreaseMaximumCurrentMaximumMemberCountTask>> FGuildDomain::IncreaseMaximumCurrentMaximumMemberCount(
        Request::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FIncreaseMaximumCurrentMaximumMemberCountTask>>(this->AsShared(), Request);
    }

    FGuildDomain::FDecreaseMaximumCurrentMaximumMemberCountTask::FDecreaseMaximumCurrentMaximumMemberCountTask(
        const TSharedPtr<FGuildDomain>& Self,
        const Request::FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildDomain::FDecreaseMaximumCurrentMaximumMemberCountTask::FDecreaseMaximumCurrentMaximumMemberCountTask(
        const FDecreaseMaximumCurrentMaximumMemberCountTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildDomain::FDecreaseMaximumCurrentMaximumMemberCountTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->DecreaseMaximumCurrentMaximumMemberCountByGuildName(
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

    TSharedPtr<FAsyncTask<FGuildDomain::FDecreaseMaximumCurrentMaximumMemberCountTask>> FGuildDomain::DecreaseMaximumCurrentMaximumMemberCount(
        Request::FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDecreaseMaximumCurrentMaximumMemberCountTask>>(this->AsShared(), Request);
    }

    FGuildDomain::FSetMaximumCurrentMaximumMemberCountTask::FSetMaximumCurrentMaximumMemberCountTask(
        const TSharedPtr<FGuildDomain>& Self,
        const Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildDomain::FSetMaximumCurrentMaximumMemberCountTask::FSetMaximumCurrentMaximumMemberCountTask(
        const FSetMaximumCurrentMaximumMemberCountTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildDomain::FSetMaximumCurrentMaximumMemberCountTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->SetMaximumCurrentMaximumMemberCountByGuildName(
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

    TSharedPtr<FAsyncTask<FGuildDomain::FSetMaximumCurrentMaximumMemberCountTask>> FGuildDomain::SetMaximumCurrentMaximumMemberCount(
        Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetMaximumCurrentMaximumMemberCountTask>>(this->AsShared(), Request);
    }

    FGuildDomain::FAcceptTask::FAcceptTask(
        const TSharedPtr<FGuildDomain>& Self,
        const Request::FAcceptRequestByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildDomain::FAcceptTask::FAcceptTask(
        const FAcceptTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildDomain::FAcceptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->AcceptRequestByGuildName(
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
                Self->Gs2->Cache->Delete(Gs2::Guild::Model::FReceiveMemberRequest::TypeName, ParentKey, Key);
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
                Self->Gs2->Cache->Delete(Gs2::Guild::Model::FGuild::TypeName, ParentKey, Key);
            }
        }
        auto Domain = MakeShared<Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Request->GetGuildModelName(),
            Request->GetGuildName(),
            Request->GetFromUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGuildDomain::FAcceptTask>> FGuildDomain::Accept(
        Request::FAcceptRequestByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAcceptTask>>(this->AsShared(), Request);
    }

    FGuildDomain::FRejectTask::FRejectTask(
        const TSharedPtr<FGuildDomain>& Self,
        const Request::FRejectRequestByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGuildDomain::FRejectTask::FRejectTask(
        const FRejectTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildDomain::FRejectTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->RejectRequestByGuildName(
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
                Self->Gs2->Cache->Delete(Gs2::Guild::Model::FReceiveMemberRequest::TypeName, ParentKey, Key);
            }
        }
        auto Domain = MakeShared<Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Request->GetGuildModelName(),
            Request->GetGuildName(),
            Request->GetFromUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGuildDomain::FRejectTask>> FGuildDomain::Reject(
        Request::FRejectRequestByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRejectTask>>(this->AsShared(), Request);
    }

    Gs2::Guild::Domain::Iterator::FDescribeReceiveRequestsByGuildNameIteratorPtr FGuildDomain::ReceiveRequestsByGuildName(
    ) const
    {
        return MakeShared<Gs2::Guild::Domain::Iterator::FDescribeReceiveRequestsByGuildNameIterator>(
            Gs2,
            Client,
            NamespaceName,
            GuildModelName,
            GuildName
        );
    }

    Gs2::Core::Domain::CallbackID FGuildDomain::SubscribeReceiveRequestsByGuildName(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Guild::Model::FReceiveMemberRequest::TypeName,
            Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheParentKey(
                NamespaceName,
                GuildModelName,
                GuildName,
                "ReceiveMemberRequest"
            ),
            Callback
        );
    }

    void FGuildDomain::UnsubscribeReceiveRequestsByGuildName(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Guild::Model::FReceiveMemberRequest::TypeName,
            Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheParentKey(
                NamespaceName,
                GuildModelName,
                GuildName,
                "ReceiveMemberRequest"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain> FGuildDomain::ReceiveMemberRequest(
        const FString FromUserId
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain>(
            Gs2,
            Service,
            NamespaceName,
            GuildModelName,
            GuildName,
            FromUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(FromUserId)
        );
    }

    FString FGuildDomain::CreateCacheParentKey(
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

    FString FGuildDomain::CreateCacheKey(
        TOptional<FString> GuildModelName,
        TOptional<FString> GuildName
    )
    {
        return FString("") +
            (GuildModelName.IsSet() ? *GuildModelName : "null") + ":" + 
            (GuildName.IsSet() ? *GuildName : "null");
    }

    FGuildDomain::FModelTask::FModelTask(
        const TSharedPtr<FGuildDomain> Self,
        const Gs2::Auth::Model::FAccessTokenPtr accessToken
    ): Self(Self), accessToken(accessToken)
    {

    }

    FGuildDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self), accessToken(From.accessToken)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FGuild>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Guild::Model::FGuild> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Guild::Model::FGuild>(
            Self->ParentKey,
            Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                Self->GuildModelName,
                Self->GuildName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Guild::Request::FGetGuildRequest>()
                    ->WithAccessToken(*accessToken->GetToken())
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
                    Self->GuildName
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
                    Self->GuildName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGuildDomain::FModelTask>> FGuildDomain::Model(
        Gs2::Auth::Model::FAccessTokenPtr accessToken
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGuildDomain::FModelTask>>(
            this->AsShared(),
            accessToken
        );
    }

    Gs2::Core::Domain::CallbackID FGuildDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FGuildPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FGuild::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                GuildModelName,
                GuildName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FGuild>(obj));
            }
        );
    }

    void FGuildDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Guild::Model::FGuild::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
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

