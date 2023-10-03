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

#include "Limit/Domain/Model/CounterAccessToken.h"
#include "Limit/Domain/Model/Counter.h"
#include "Limit/Domain/Model/Namespace.h"
#include "Limit/Domain/Model/Counter.h"
#include "Limit/Domain/Model/CounterAccessToken.h"
#include "Limit/Domain/Model/LimitModelMaster.h"
#include "Limit/Domain/Model/CurrentLimitMaster.h"
#include "Limit/Domain/Model/LimitModel.h"
#include "Limit/Domain/Model/User.h"
#include "Limit/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Limit::Domain::Model
{

    FCounterAccessTokenDomain::FCounterAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> LimitName,
        const TOptional<FString> CounterName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Limit::FGs2LimitRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        LimitName(LimitName),
        CounterName(CounterName),
        ParentKey(Gs2::Limit::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Counter"
        ))
    {
    }

    FCounterAccessTokenDomain::FCounterAccessTokenDomain(
        const FCounterAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        LimitName(From.LimitName),
        CounterName(From.CounterName),
        ParentKey(From.ParentKey)
    {

    }

    FCounterAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FCounterAccessTokenDomain> Self,
        const Request::FGetCounterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCounterAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Model::FCounter>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithLimitName(Self->LimitName)
            ->WithCounterName(Self->CounterName);
        const auto Future = Self->Client->GetCounter(
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
                    Self->UserId(),
                    "Counter"
                );
                const auto Key = Gs2::Limit::Domain::Model::FCounterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetLimitName(),
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
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

    TSharedPtr<FAsyncTask<FCounterAccessTokenDomain::FGetTask>> FCounterAccessTokenDomain::Get(
        Request::FGetCounterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCounterAccessTokenDomain::FCountUpTask::FCountUpTask(
        const TSharedPtr<FCounterAccessTokenDomain> Self,
        const Request::FCountUpRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCounterAccessTokenDomain::FCountUpTask::FCountUpTask(
        const FCountUpTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterAccessTokenDomain::FCountUpTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FCounterAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithLimitName(Self->LimitName)
            ->WithCounterName(Self->CounterName);
        const auto Future = Self->Client->CountUp(
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
                    Self->UserId(),
                    "Counter"
                );
                const auto Key = Gs2::Limit::Domain::Model::FCounterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetLimitName(),
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
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

    TSharedPtr<FAsyncTask<FCounterAccessTokenDomain::FCountUpTask>> FCounterAccessTokenDomain::CountUp(
        Request::FCountUpRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCountUpTask>>(this->AsShared(), Request);
    }

    FCounterAccessTokenDomain::FVerifyTask::FVerifyTask(
        const TSharedPtr<FCounterAccessTokenDomain> Self,
        const Request::FVerifyCounterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCounterAccessTokenDomain::FVerifyTask::FVerifyTask(
        const FVerifyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterAccessTokenDomain::FVerifyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FCounterAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithLimitName(Self->LimitName)
            ->WithCounterName(Self->CounterName);
        const auto Future = Self->Client->VerifyCounter(
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

    TSharedPtr<FAsyncTask<FCounterAccessTokenDomain::FVerifyTask>> FCounterAccessTokenDomain::Verify(
        Request::FVerifyCounterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyTask>>(this->AsShared(), Request);
    }

    FString FCounterAccessTokenDomain::CreateCacheParentKey(
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

    FString FCounterAccessTokenDomain::CreateCacheKey(
        TOptional<FString> LimitName,
        TOptional<FString> CounterName
    )
    {
        return FString("") +
            (LimitName.IsSet() ? *LimitName : "null") + ":" + 
            (CounterName.IsSet() ? *CounterName : "null");
    }

    FCounterAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FCounterAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FCounterAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Model::FCounter>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Limit::Model::FCounter> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Limit::Model::FCounter>(
            Self->ParentKey,
            Gs2::Limit::Domain::Model::FCounterDomain::CreateCacheKey(
                Self->LimitName,
                Self->CounterName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Limit::Request::FGetCounterRequest>()
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
                Self->Cache->Put(
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
            Self->Cache->TryGet<Gs2::Limit::Model::FCounter>(
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

    TSharedPtr<FAsyncTask<FCounterAccessTokenDomain::FModelTask>> FCounterAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCounterAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCounterAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Limit::Model::FCounterPtr)> Callback
    )
    {
        return Cache->Subscribe(
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

    void FCounterAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
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

