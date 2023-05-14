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

#include "Schedule/Domain/Model/EventMaster.h"
#include "Schedule/Domain/Model/Namespace.h"
#include "Schedule/Domain/Model/EventMaster.h"
#include "Schedule/Domain/Model/Trigger.h"
#include "Schedule/Domain/Model/TriggerAccessToken.h"
#include "Schedule/Domain/Model/Event.h"
#include "Schedule/Domain/Model/EventAccessToken.h"
#include "Schedule/Domain/Model/CurrentEventMaster.h"
#include "Schedule/Domain/Model/User.h"
#include "Schedule/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Schedule::Domain::Model
{

    FEventMasterDomain::FEventMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> EventName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Schedule::FGs2ScheduleRestClient>(Session)),
        NamespaceName(NamespaceName),
        EventName(EventName),
        ParentKey(Gs2::Schedule::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "EventMaster"
        ))
    {
    }

    FEventMasterDomain::FEventMasterDomain(
        const FEventMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FEventMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FEventMasterDomain> Self,
        const Request::FGetEventMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FEventMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEventMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FEventMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithEventName(Self->EventName);
        const auto Future = Self->Client->GetEventMaster(
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
                const auto ParentKey = Gs2::Schedule::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "EventMaster"
                );
                const auto Key = Gs2::Schedule::Domain::Model::FEventMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Schedule::Model::FEventMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FEventMasterDomain::FGetTask>> FEventMasterDomain::Get(
        Request::FGetEventMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FEventMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FEventMasterDomain> Self,
        const Request::FUpdateEventMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FEventMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEventMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FEventMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithEventName(Self->EventName);
        const auto Future = Self->Client->UpdateEventMaster(
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
                const auto ParentKey = Gs2::Schedule::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "EventMaster"
                );
                const auto Key = Gs2::Schedule::Domain::Model::FEventMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Schedule::Model::FEventMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FEventMasterDomain::FUpdateTask>> FEventMasterDomain::Update(
        Request::FUpdateEventMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FEventMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FEventMasterDomain> Self,
        const Request::FDeleteEventMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FEventMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEventMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FEventMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithEventName(Self->EventName);
        const auto Future = Self->Client->DeleteEventMaster(
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
                const auto ParentKey = Gs2::Schedule::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "EventMaster"
                );
                const auto Key = Gs2::Schedule::Domain::Model::FEventMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Schedule::Model::FEventMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEventMasterDomain::FDeleteTask>> FEventMasterDomain::Delete(
        Request::FDeleteEventMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FEventMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> EventName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (EventName.IsSet() ? *EventName : "null") + ":" +
            ChildType;
    }

    FString FEventMasterDomain::CreateCacheKey(
        TOptional<FString> EventName
    )
    {
        return FString() +
            (EventName.IsSet() ? *EventName : "null");
    }

    FEventMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FEventMasterDomain> Self
    ): Self(Self)
    {

    }

    FEventMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEventMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FEventMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Schedule::Model::FEventMaster>(
            Self->ParentKey,
            Gs2::Schedule::Domain::Model::FEventMasterDomain::CreateCacheKey(
                Self->EventName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Schedule::Request::FGetEventMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "eventMaster")
                    {
                        Self->Cache->Delete(
                            Gs2::Schedule::Model::FEventMaster::TypeName,
                            Self->ParentKey,
                            Gs2::Schedule::Domain::Model::FEventMasterDomain::CreateCacheKey(
                                Self->EventName
                            )
                        );
                    }
                    else
                    {
                        return Future->GetTask().Error();
                    }
                }
                else
                {
                    return Future->GetTask().Error();
                }
            }
            Value = Self->Cache->Get<Gs2::Schedule::Model::FEventMaster>(
                Self->ParentKey,
                Gs2::Schedule::Domain::Model::FEventMasterDomain::CreateCacheKey(
                    Self->EventName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEventMasterDomain::FModelTask>> FEventMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FEventMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

