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

#include "Mission/Domain/Model/Counter.h"
#include "Mission/Domain/Model/Complete.h"
#include "Mission/Domain/Model/CompleteAccessToken.h"
#include "Mission/Domain/Model/CounterModelMaster.h"
#include "Mission/Domain/Model/MissionGroupModelMaster.h"
#include "Mission/Domain/Model/Namespace.h"
#include "Mission/Domain/Model/Counter.h"
#include "Mission/Domain/Model/CounterAccessToken.h"
#include "Mission/Domain/Model/CurrentMissionMaster.h"
#include "Mission/Domain/Model/CounterModel.h"
#include "Mission/Domain/Model/MissionGroupModel.h"
#include "Mission/Domain/Model/MissionTaskModel.h"
#include "Mission/Domain/Model/MissionTaskModelMaster.h"
#include "Mission/Domain/Model/User.h"
#include "Mission/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Mission::Domain::Model
{

    FCounterDomain::FCounterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Mission::Domain::FGs2MissionDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> CounterName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Mission::FGs2MissionRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        CounterName(CounterName),
        ParentKey(Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Counter"
        ))
    {
    }

    FCounterDomain::FCounterDomain(
        const FCounterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        CounterName(From.CounterName),
        ParentKey(From.ParentKey)
    {

    }

    FCounterDomain::FIncreaseTask::FIncreaseTask(
        const TSharedPtr<FCounterDomain>& Self,
        const Request::FIncreaseCounterByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCounterDomain::FIncreaseTask::FIncreaseTask(
        const FIncreaseTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterDomain::FIncreaseTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCounterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCounterName(Self->CounterName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->IncreaseCounterByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCounterDomain::FIncreaseTask>> FCounterDomain::Increase(
        Request::FIncreaseCounterByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FIncreaseTask>>(this->AsShared(), Request);
    }

    FCounterDomain::FSetTask::FSetTask(
        const TSharedPtr<FCounterDomain>& Self,
        const Request::FSetCounterByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCounterDomain::FSetTask::FSetTask(
        const FSetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterDomain::FSetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCounterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCounterName(Self->CounterName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->SetCounterByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCounterDomain::FSetTask>> FCounterDomain::Set(
        Request::FSetCounterByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetTask>>(this->AsShared(), Request);
    }

    FCounterDomain::FDecreaseTask::FDecreaseTask(
        const TSharedPtr<FCounterDomain>& Self,
        const Request::FDecreaseCounterByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCounterDomain::FDecreaseTask::FDecreaseTask(
        const FDecreaseTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterDomain::FDecreaseTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCounterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCounterName(Self->CounterName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DecreaseCounterByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCounterDomain::FDecreaseTask>> FCounterDomain::Decrease(
        Request::FDecreaseCounterByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDecreaseTask>>(this->AsShared(), Request);
    }

    FCounterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCounterDomain>& Self,
        const Request::FGetCounterByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCounterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FCounter>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCounterName(Self->CounterName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->GetCounterByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCounterDomain::FGetTask>> FCounterDomain::Get(
        Request::FGetCounterByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCounterDomain::FVerifyValueTask::FVerifyValueTask(
        const TSharedPtr<FCounterDomain>& Self,
        const Request::FVerifyCounterValueByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCounterDomain::FVerifyValueTask::FVerifyValueTask(
        const FVerifyValueTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterDomain::FVerifyValueTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCounterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCounterName(Self->CounterName);
        const auto Future = Self->Client->VerifyCounterValueByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCounterDomain::FVerifyValueTask>> FCounterDomain::VerifyValue(
        Request::FVerifyCounterValueByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyValueTask>>(this->AsShared(), Request);
    }

    FCounterDomain::FResetTask::FResetTask(
        const TSharedPtr<FCounterDomain>& Self,
        const Request::FResetCounterByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCounterDomain::FResetTask::FResetTask(
        const FResetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterDomain::FResetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCounterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCounterName(Self->CounterName);
        const auto Future = Self->Client->ResetCounterByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCounterDomain::FResetTask>> FCounterDomain::Reset(
        Request::FResetCounterByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FResetTask>>(this->AsShared(), Request);
    }

    FCounterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FCounterDomain>& Self,
        const Request::FDeleteCounterByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCounterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCounterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCounterName(Self->CounterName);
        const auto Future = Self->Client->DeleteCounterByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCounterDomain::FDeleteTask>> FCounterDomain::Delete(
        Request::FDeleteCounterByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FCounterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> CounterName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (CounterName.IsSet() ? *CounterName : "null") + ":" +
            ChildType;
    }

    FString FCounterDomain::CreateCacheKey(
        TOptional<FString> CounterName
    )
    {
        return FString("") +
            (CounterName.IsSet() ? *CounterName : "null");
    }

    FCounterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCounterDomain> Self
    ): Self(Self)
    {

    }

    FCounterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FCounter>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Mission::Model::FCounter> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Mission::Model::FCounter>(
            Self->ParentKey,
            Gs2::Mission::Domain::Model::FCounterDomain::CreateCacheKey(
                Self->CounterName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Mission::Request::FGetCounterByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Mission::Domain::Model::FCounterDomain::CreateCacheKey(
                    Self->CounterName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Mission::Model::FCounter::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "counter")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Mission::Model::FCounter>(
                Self->ParentKey,
                Gs2::Mission::Domain::Model::FCounterDomain::CreateCacheKey(
                    Self->CounterName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCounterDomain::FModelTask>> FCounterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCounterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCounterDomain::Subscribe(
        TFunction<void(Gs2::Mission::Model::FCounterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Mission::Model::FCounter::TypeName,
            ParentKey,
            Gs2::Mission::Domain::Model::FCounterDomain::CreateCacheKey(
                CounterName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Mission::Model::FCounter>(obj));
            }
        );
    }

    void FCounterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Mission::Model::FCounter::TypeName,
            ParentKey,
            Gs2::Mission::Domain::Model::FCounterDomain::CreateCacheKey(
                CounterName
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

