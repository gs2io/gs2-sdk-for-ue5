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

#include "Guild/Domain/Model/IgnoreUser.h"
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

    FIgnoreUserDomain::FIgnoreUserDomain(
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
            "IgnoreUser"
        ))
    {
    }

    FIgnoreUserDomain::FIgnoreUserDomain(
        const FIgnoreUserDomain& From
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

    FIgnoreUserDomain::FGetTask::FGetTask(
        const TSharedPtr<FIgnoreUserDomain>& Self,
        const Request::FGetIgnoreUserByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FIgnoreUserDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FIgnoreUserDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FIgnoreUser>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->GetIgnoreUserByGuildName(
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
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIgnoreUserDomain::FGetTask>> FIgnoreUserDomain::Get(
        Request::FGetIgnoreUserByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FIgnoreUserDomain::FAddTask::FAddTask(
        const TSharedPtr<FIgnoreUserDomain>& Self,
        const Request::FAddIgnoreUserByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FIgnoreUserDomain::FAddTask::FAddTask(
        const FAddTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FIgnoreUserDomain::FAddTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FIgnoreUserDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->AddIgnoreUserByGuildName(
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
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIgnoreUserDomain::FAddTask>> FIgnoreUserDomain::Add(
        Request::FAddIgnoreUserByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAddTask>>(this->AsShared(), Request);
    }

    FIgnoreUserDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FIgnoreUserDomain>& Self,
        const Request::FDeleteIgnoreUserByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FIgnoreUserDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FIgnoreUserDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FIgnoreUserDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->DeleteIgnoreUserByGuildName(
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
                    "IgnoreUser"
                );
                const auto Key = Gs2::Guild::Domain::Model::FIgnoreUserDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Delete(Gs2::Guild::Model::FIgnoreUser::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIgnoreUserDomain::FDeleteTask>> FIgnoreUserDomain::Delete(
        Request::FDeleteIgnoreUserByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FIgnoreUserDomain::CreateCacheParentKey(
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

    FString FIgnoreUserDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FIgnoreUserDomain::FModelTask::FModelTask(
        const TSharedPtr<FIgnoreUserDomain> Self
    ): Self(Self)
    {

    }

    FIgnoreUserDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FIgnoreUserDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FIgnoreUser>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Guild::Model::FIgnoreUser> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Guild::Model::FIgnoreUser>(
            Self->ParentKey,
            Gs2::Guild::Domain::Model::FIgnoreUserDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Guild::Request::FGetIgnoreUserByGuildNameRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Guild::Domain::Model::FIgnoreUserDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FIgnoreUser::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "ignoreUser")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Guild::Model::FIgnoreUser>(
                Self->ParentKey,
                Gs2::Guild::Domain::Model::FIgnoreUserDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIgnoreUserDomain::FModelTask>> FIgnoreUserDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FIgnoreUserDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FIgnoreUserDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FIgnoreUserPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FIgnoreUser::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FIgnoreUserDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FIgnoreUser>(obj));
            }
        );
    }

    void FIgnoreUserDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Guild::Model::FIgnoreUser::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FIgnoreUserDomain::CreateCacheKey(
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

