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

#include "Guild/Domain/Model/LastGuildMasterActivity.h"
#include "Guild/Domain/Model/Namespace.h"
#include "Guild/Domain/Model/GuildModelMaster.h"
#include "Guild/Domain/Model/GuildModel.h"
#include "Guild/Domain/Model/User.h"
#include "Guild/Domain/Model/UserAccessToken.h"
#include "Guild/Domain/Model/Guild.h"
#include "Guild/Domain/Model/JoinedGuild.h"
#include "Guild/Domain/Model/JoinedGuildAccessToken.h"
#include "Guild/Domain/Model/LastGuildMasterActivity.h"
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

    FLastGuildMasterActivityDomain::FLastGuildMasterActivityDomain(
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
        ParentKey(Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheParentKey(
            NamespaceName,
            GuildModelName,
            GuildName,
            "LastGuildMasterActivity"
        ))
    {
    }

    FLastGuildMasterActivityDomain::FLastGuildMasterActivityDomain(
        const FLastGuildMasterActivityDomain& From
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

    FLastGuildMasterActivityDomain::FGetTask::FGetTask(
        const TSharedPtr<FLastGuildMasterActivityDomain>& Self,
        const Request::FGetLastGuildMasterActivityByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLastGuildMasterActivityDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLastGuildMasterActivityDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FLastGuildMasterActivity>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->GetLastGuildMasterActivityByGuildName(
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

    TSharedPtr<FAsyncTask<FLastGuildMasterActivityDomain::FGetTask>> FLastGuildMasterActivityDomain::Get(
        Request::FGetLastGuildMasterActivityByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FLastGuildMasterActivityDomain::FPromoteSeniorMemberTask::FPromoteSeniorMemberTask(
        const TSharedPtr<FLastGuildMasterActivityDomain>& Self,
        const Request::FPromoteSeniorMemberByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLastGuildMasterActivityDomain::FPromoteSeniorMemberTask::FPromoteSeniorMemberTask(
        const FPromoteSeniorMemberTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLastGuildMasterActivityDomain::FPromoteSeniorMemberTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FLastGuildMasterActivityDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->PromoteSeniorMemberByGuildName(
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
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLastGuildMasterActivityDomain::FPromoteSeniorMemberTask>> FLastGuildMasterActivityDomain::PromoteSeniorMember(
        Request::FPromoteSeniorMemberByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPromoteSeniorMemberTask>>(this->AsShared(), Request);
    }

    FString FLastGuildMasterActivityDomain::CreateCacheParentKey(
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

    FString FLastGuildMasterActivityDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FLastGuildMasterActivityDomain::FModelTask::FModelTask(
        const TSharedPtr<FLastGuildMasterActivityDomain> Self
    ): Self(Self)
    {

    }

    FLastGuildMasterActivityDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FLastGuildMasterActivityDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FLastGuildMasterActivity>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Guild::Model::FLastGuildMasterActivity> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Guild::Model::FLastGuildMasterActivity>(
            Self->ParentKey,
            Gs2::Guild::Domain::Model::FLastGuildMasterActivityDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Guild::Request::FGetLastGuildMasterActivityByGuildNameRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Guild::Domain::Model::FLastGuildMasterActivityDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FLastGuildMasterActivity::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "lastGuildMasterActivity")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Guild::Model::FLastGuildMasterActivity>(
                Self->ParentKey,
                Gs2::Guild::Domain::Model::FLastGuildMasterActivityDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLastGuildMasterActivityDomain::FModelTask>> FLastGuildMasterActivityDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FLastGuildMasterActivityDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FLastGuildMasterActivityDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FLastGuildMasterActivityPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FLastGuildMasterActivity::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FLastGuildMasterActivityDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FLastGuildMasterActivity>(obj));
            }
        );
    }

    void FLastGuildMasterActivityDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Guild::Model::FLastGuildMasterActivity::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FLastGuildMasterActivityDomain::CreateCacheKey(
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

