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

#include "Limit/Domain/Model/Counter.h"
#include "Limit/Domain/Model/Namespace.h"
#include "Limit/Domain/Model/Counter.h"
#include "Limit/Domain/Model/CounterAccessToken.h"
#include "Limit/Domain/Model/LimitModelMaster.h"
#include "Limit/Domain/Model/CurrentLimitMaster.h"
#include "Limit/Domain/Model/LimitModel.h"
#include "Limit/Domain/Model/User.h"
#include "Limit/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Limit::Domain::Model
{

    FCounterDomain::FCounterDomain(
        const Core::Domain::FGs2Ptr Gs2,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> LimitName,
        const TOptional<FString> CounterName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Limit::FGs2LimitRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        LimitName(LimitName),
        CounterName(CounterName),
        ParentKey(Gs2::Limit::Domain::Model::FUserDomain::CreateCacheParentKey(
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
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        LimitName(From.LimitName),
        CounterName(From.CounterName),
        ParentKey(From.ParentKey)
    {

    }

    FCounterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCounterDomain> Self,
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
        TSharedPtr<TSharedPtr<Gs2::Limit::Model::FCounter>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithLimitName(Self->LimitName)
            ->WithCounterName(Self->CounterName);
        const auto Future = Self->Client->GetCounterByUserId(
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
                const auto ParentKey = Gs2::Limit::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Counter"
                );
                const auto Key = Gs2::Limit::Domain::Model::FCounterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetLimitName(),
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Limit::Model::FCounter::TypeName,
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

    TSharedPtr<FAsyncTask<FCounterDomain::FGetTask>> FCounterDomain::Get(
        Request::FGetCounterByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCounterDomain::FCountUpTask::FCountUpTask(
        const TSharedPtr<FCounterDomain> Self,
        const Request::FCountUpByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCounterDomain::FCountUpTask::FCountUpTask(
        const FCountUpTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterDomain::FCountUpTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FCounterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithLimitName(Self->LimitName)
            ->WithCounterName(Self->CounterName);
        const auto Future = Self->Client->CountUpByUserId(
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
                const auto ParentKey = Gs2::Limit::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Counter"
                );
                const auto Key = Gs2::Limit::Domain::Model::FCounterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetLimitName(),
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Limit::Model::FCounter::TypeName,
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

    TSharedPtr<FAsyncTask<FCounterDomain::FCountUpTask>> FCounterDomain::CountUp(
        Request::FCountUpByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCountUpTask>>(this->AsShared(), Request);
    }

    FCounterDomain::FCountDownTask::FCountDownTask(
        const TSharedPtr<FCounterDomain> Self,
        const Request::FCountDownByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCounterDomain::FCountDownTask::FCountDownTask(
        const FCountDownTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterDomain::FCountDownTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FCounterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithLimitName(Self->LimitName)
            ->WithCounterName(Self->CounterName);
        const auto Future = Self->Client->CountDownByUserId(
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
                const auto ParentKey = Gs2::Limit::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Counter"
                );
                const auto Key = Gs2::Limit::Domain::Model::FCounterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetLimitName(),
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Limit::Model::FCounter::TypeName,
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

    TSharedPtr<FAsyncTask<FCounterDomain::FCountDownTask>> FCounterDomain::CountDown(
        Request::FCountDownByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCountDownTask>>(this->AsShared(), Request);
    }

    FCounterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FCounterDomain> Self,
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
        TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FCounterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithLimitName(Self->LimitName)
            ->WithCounterName(Self->CounterName);
        const auto Future = Self->Client->DeleteCounterByUserId(
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
                const auto ParentKey = Gs2::Limit::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Counter"
                );
                const auto Key = Gs2::Limit::Domain::Model::FCounterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetLimitName(),
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Limit::Model::FCounter::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCounterDomain::FDeleteTask>> FCounterDomain::Delete(
        Request::FDeleteCounterByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FCounterDomain::FVerifyTask::FVerifyTask(
        const TSharedPtr<FCounterDomain> Self,
        const Request::FVerifyCounterByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCounterDomain::FVerifyTask::FVerifyTask(
        const FVerifyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterDomain::FVerifyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FCounterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithLimitName(Self->LimitName)
            ->WithCounterName(Self->CounterName);
        const auto Future = Self->Client->VerifyCounterByUserId(
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

    TSharedPtr<FAsyncTask<FCounterDomain::FVerifyTask>> FCounterDomain::Verify(
        Request::FVerifyCounterByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyTask>>(this->AsShared(), Request);
    }

    FString FCounterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> LimitName,
        TOptional<FString> CounterName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (LimitName.IsSet() ? *LimitName : "null") + ":" +
            (CounterName.IsSet() ? *CounterName : "null") + ":" +
            ChildType;
    }

    FString FCounterDomain::CreateCacheKey(
        TOptional<FString> LimitName,
        TOptional<FString> CounterName
    )
    {
        return FString("") +
            (LimitName.IsSet() ? *LimitName : "null") + ":" + 
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
        TSharedPtr<TSharedPtr<Gs2::Limit::Model::FCounter>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Limit::Model::FCounter> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Limit::Model::FCounter>(
            Self->ParentKey,
            Gs2::Limit::Domain::Model::FCounterDomain::CreateCacheKey(
                Self->LimitName,
                Self->CounterName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Limit::Request::FGetCounterByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Limit::Domain::Model::FCounterDomain::CreateCacheKey(
                    Self->LimitName,
                    Self->CounterName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Limit::Model::FCounter::TypeName,
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
            Self->Gs2->Cache->TryGet<Gs2::Limit::Model::FCounter>(
                Self->ParentKey,
                Gs2::Limit::Domain::Model::FCounterDomain::CreateCacheKey(
                    Self->LimitName,
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
        TFunction<void(Gs2::Limit::Model::FCounterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Limit::Model::FCounter::TypeName,
            ParentKey,
            Gs2::Limit::Domain::Model::FCounterDomain::CreateCacheKey(
                LimitName,
                CounterName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Limit::Model::FCounter>(obj));
            }
        );
    }

    void FCounterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Limit::Model::FCounter::TypeName,
            ParentKey,
            Gs2::Limit::Domain::Model::FCounterDomain::CreateCacheKey(
                LimitName,
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

