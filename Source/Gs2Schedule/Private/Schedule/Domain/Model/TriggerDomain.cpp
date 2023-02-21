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

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Schedule::Domain::Model
{

    FTriggerDomain::FTriggerDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> TriggerName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Schedule::FGs2ScheduleRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        TriggerName(TriggerName),
        ParentKey(Gs2::Schedule::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Trigger"
        ))
    {
    }

    FTriggerDomain::FTriggerDomain(
        const FTriggerDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FTriggerDomain::FGetTask::FGetTask(
        const TSharedPtr<FTriggerDomain> Self,
        const Request::FGetTriggerByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTriggerDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTriggerDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FTrigger>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithTriggerName(Self->TriggerName);
        const auto Future = Self->Client->GetTriggerByUserId(
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
                    Self->UserId,
                    "Trigger"
                );
                const auto Key = Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::Schedule::Model::FTrigger>(
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

    TSharedPtr<FAsyncTask<FTriggerDomain::FGetTask>> FTriggerDomain::Get(
        Request::FGetTriggerByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FTriggerDomain::FTriggerTask::FTriggerTask(
        const TSharedPtr<FTriggerDomain> Self,
        const Request::FTriggerByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTriggerDomain::FTriggerTask::FTriggerTask(
        const FTriggerTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTriggerDomain::FTriggerTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FTriggerDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithTriggerName(Self->TriggerName);
        const auto Future = Self->Client->TriggerByUserId(
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
                    Self->UserId,
                    "Trigger"
                );
                const auto Key = Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::Schedule::Model::FTrigger>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
                Self->Cache->ClearListCache<Gs2::Schedule::Model::FEvent>(
                    ParentKey.Replace(TEXT("Trigger"), TEXT("Event"))
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTriggerDomain::FTriggerTask>> FTriggerDomain::Trigger(
        Request::FTriggerByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FTriggerTask>>(this->AsShared(), Request);
    }

    FTriggerDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FTriggerDomain> Self,
        const Request::FDeleteTriggerByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTriggerDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTriggerDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FTriggerDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithTriggerName(Self->TriggerName);
        const auto Future = Self->Client->DeleteTriggerByUserId(
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
                    Self->UserId,
                    "Trigger"
                );
                const auto Key = Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete<Gs2::Schedule::Model::FTrigger>(ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTriggerDomain::FDeleteTask>> FTriggerDomain::Delete(
        Request::FDeleteTriggerByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FTriggerDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> TriggerName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (TriggerName.IsSet() ? *TriggerName : "null") + ":" +
            ChildType;
    }

    FString FTriggerDomain::CreateCacheKey(
        TOptional<FString> TriggerName
    )
    {
        return FString() +
            (TriggerName.IsSet() ? *TriggerName : "null");
    }

    FTriggerDomain::FModelTask::FModelTask(
        const TSharedPtr<FTriggerDomain> Self
    ): Self(Self)
    {

    }

    FTriggerDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FTriggerDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FTrigger>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Schedule::Model::FTrigger>(
            Self->ParentKey,
            Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                Self->TriggerName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Schedule::Request::FGetTriggerByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "trigger")
                    {
                        Self->Cache->Delete<Gs2::Schedule::Model::FTrigger>(
                            Self->ParentKey,
                            Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                                Self->TriggerName
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
            Value = Self->Cache->Get<Gs2::Schedule::Model::FTrigger>(
                Self->ParentKey,
                Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                    Self->TriggerName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTriggerDomain::FModelTask>> FTriggerDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FTriggerDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

