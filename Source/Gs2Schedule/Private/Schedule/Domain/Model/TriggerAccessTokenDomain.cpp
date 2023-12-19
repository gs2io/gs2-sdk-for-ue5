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

#include "Schedule/Domain/Model/TriggerAccessToken.h"
#include "Schedule/Domain/Model/Trigger.h"
#include "Schedule/Domain/Model/Namespace.h"
#include "Schedule/Domain/Model/EventMaster.h"
#include "Schedule/Domain/Model/Trigger.h"
#include "Schedule/Domain/Model/TriggerAccessToken.h"
#include "Schedule/Domain/Model/Event.h"
#include "Schedule/Domain/Model/EventAccessToken.h"
#include "Schedule/Domain/Model/CurrentEventMaster.h"
#include "Schedule/Domain/Model/User.h"
#include "Schedule/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Schedule::Domain::Model
{

    FTriggerAccessTokenDomain::FTriggerAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> TriggerName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Schedule::FGs2ScheduleRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        TriggerName(TriggerName),
        ParentKey(Gs2::Schedule::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Trigger"
        ))
    {
    }

    FTriggerAccessTokenDomain::FTriggerAccessTokenDomain(
        const FTriggerAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        TriggerName(From.TriggerName),
        ParentKey(From.ParentKey)
    {

    }

    FTriggerAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FTriggerAccessTokenDomain>& Self,
        const Request::FGetTriggerRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTriggerAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTriggerAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FTrigger>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithTriggerName(Self->TriggerName);
        const auto Future = Self->Client->GetTrigger(
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
                const auto ParentKey = Gs2::Schedule::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Trigger"
                );
                const auto Key = Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Schedule::Model::FTrigger::TypeName,
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

    TSharedPtr<FAsyncTask<FTriggerAccessTokenDomain::FGetTask>> FTriggerAccessTokenDomain::Get(
        Request::FGetTriggerRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FTriggerAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FTriggerAccessTokenDomain>& Self,
        const Request::FDeleteTriggerRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTriggerAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTriggerAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FTriggerAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithTriggerName(Self->TriggerName);
        const auto Future = Self->Client->DeleteTrigger(
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
                const auto ParentKey = Gs2::Schedule::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Trigger"
                );
                const auto Key = Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Schedule::Model::FTrigger::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTriggerAccessTokenDomain::FDeleteTask>> FTriggerAccessTokenDomain::Delete(
        Request::FDeleteTriggerRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FTriggerAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> TriggerName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (TriggerName.IsSet() ? *TriggerName : "null") + ":" +
            ChildType;
    }

    FString FTriggerAccessTokenDomain::CreateCacheKey(
        TOptional<FString> TriggerName
    )
    {
        return FString("") +
            (TriggerName.IsSet() ? *TriggerName : "null");
    }

    FTriggerAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FTriggerAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FTriggerAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FTriggerAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FTrigger>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Schedule::Model::FTrigger> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Schedule::Model::FTrigger>(
            Self->ParentKey,
            Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                Self->TriggerName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Schedule::Request::FGetTriggerRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                    Self->TriggerName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Schedule::Model::FTrigger::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "trigger")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Schedule::Model::FTrigger>(
                Self->ParentKey,
                Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                    Self->TriggerName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTriggerAccessTokenDomain::FModelTask>> FTriggerAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FTriggerAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FTriggerAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Schedule::Model::FTriggerPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Schedule::Model::FTrigger::TypeName,
            ParentKey,
            Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                TriggerName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Schedule::Model::FTrigger>(obj));
            }
        );
    }

    void FTriggerAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Schedule::Model::FTrigger::TypeName,
            ParentKey,
            Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                TriggerName
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

