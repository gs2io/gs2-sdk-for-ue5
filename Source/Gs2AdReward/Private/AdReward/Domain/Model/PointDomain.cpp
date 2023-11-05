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

#include "AdReward/Domain/Model/Point.h"
#include "AdReward/Domain/Model/Namespace.h"
#include "AdReward/Domain/Model/User.h"
#include "AdReward/Domain/Model/UserAccessToken.h"
#include "AdReward/Domain/Model/Point.h"
#include "AdReward/Domain/Model/PointAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::AdReward::Domain::Model
{

    FPointDomain::FPointDomain(
        const Core::Domain::FGs2Ptr Gs2,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::AdReward::FGs2AdRewardRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::AdReward::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Point"
        ))
    {
    }

    FPointDomain::FPointDomain(
        const FPointDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FPointDomain::FGetTask::FGetTask(
        const TSharedPtr<FPointDomain> Self,
        const Request::FGetPointByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPointDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPointDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::AdReward::Model::FPoint>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->GetPointByUserId(
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
                const auto ParentKey = Gs2::AdReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Point"
                );
                const auto Key = Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::AdReward::Model::FPoint::TypeName,
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

    TSharedPtr<FAsyncTask<FPointDomain::FGetTask>> FPointDomain::Get(
        Request::FGetPointByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FPointDomain::FAcquireTask::FAcquireTask(
        const TSharedPtr<FPointDomain> Self,
        const Request::FAcquirePointByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPointDomain::FAcquireTask::FAcquireTask(
        const FAcquireTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPointDomain::FAcquireTask::Action(
        TSharedPtr<TSharedPtr<Gs2::AdReward::Domain::Model::FPointDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->AcquirePointByUserId(
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
                const auto ParentKey = Gs2::AdReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Point"
                );
                const auto Key = Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::AdReward::Model::FPoint::TypeName,
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

    TSharedPtr<FAsyncTask<FPointDomain::FAcquireTask>> FPointDomain::Acquire(
        Request::FAcquirePointByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAcquireTask>>(this->AsShared(), Request);
    }

    FPointDomain::FConsumeTask::FConsumeTask(
        const TSharedPtr<FPointDomain> Self,
        const Request::FConsumePointByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPointDomain::FConsumeTask::FConsumeTask(
        const FConsumeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPointDomain::FConsumeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::AdReward::Domain::Model::FPointDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->ConsumePointByUserId(
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
                const auto ParentKey = Gs2::AdReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Point"
                );
                const auto Key = Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::AdReward::Model::FPoint::TypeName,
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

    TSharedPtr<FAsyncTask<FPointDomain::FConsumeTask>> FPointDomain::Consume(
        Request::FConsumePointByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FConsumeTask>>(this->AsShared(), Request);
    }

    FPointDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FPointDomain> Self,
        const Request::FDeletePointByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPointDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPointDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::AdReward::Domain::Model::FPointDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DeletePointByUserId(
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
                const auto ParentKey = Gs2::AdReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Point"
                );
                const auto Key = Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Delete(Gs2::AdReward::Model::FPoint::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPointDomain::FDeleteTask>> FPointDomain::Delete(
        Request::FDeletePointByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FPointDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FPointDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FPointDomain::FModelTask::FModelTask(
        const TSharedPtr<FPointDomain> Self
    ): Self(Self)
    {

    }

    FPointDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FPointDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::AdReward::Model::FPoint>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::AdReward::Model::FPoint> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::AdReward::Model::FPoint>(
            Self->ParentKey,
            Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::AdReward::Request::FGetPointByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::AdReward::Model::FPoint::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "point")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::AdReward::Model::FPoint>(
                Self->ParentKey,
                Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPointDomain::FModelTask>> FPointDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FPointDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FPointDomain::Subscribe(
        TFunction<void(Gs2::AdReward::Model::FPointPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::AdReward::Model::FPoint::TypeName,
            ParentKey,
            Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::AdReward::Model::FPoint>(obj));
            }
        );
    }

    void FPointDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::AdReward::Model::FPoint::TypeName,
            ParentKey,
            Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
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

