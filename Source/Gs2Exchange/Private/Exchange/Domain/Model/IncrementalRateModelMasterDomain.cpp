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

#include "Exchange/Domain/Model/IncrementalRateModelMaster.h"
#include "Exchange/Domain/Model/Namespace.h"
#include "Exchange/Domain/Model/RateModel.h"
#include "Exchange/Domain/Model/RateModelMaster.h"
#include "Exchange/Domain/Model/IncrementalRateModel.h"
#include "Exchange/Domain/Model/IncrementalRateModelMaster.h"
#include "Exchange/Domain/Model/Exchange.h"
#include "Exchange/Domain/Model/ExchangeAccessToken.h"
#include "Exchange/Domain/Model/CurrentRateMaster.h"
#include "Exchange/Domain/Model/Await.h"
#include "Exchange/Domain/Model/AwaitAccessToken.h"
#include "Exchange/Domain/Model/User.h"
#include "Exchange/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Exchange::Domain::Model
{

    FIncrementalRateModelMasterDomain::FIncrementalRateModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Exchange::Domain::FGs2ExchangeDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RateName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Exchange::FGs2ExchangeRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        RateName(RateName),
        ParentKey(Gs2::Exchange::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "IncrementalRateModelMaster"
        ))
    {
    }

    FIncrementalRateModelMasterDomain::FIncrementalRateModelMasterDomain(
        const FIncrementalRateModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RateName(From.RateName),
        ParentKey(From.ParentKey)
    {

    }

    FIncrementalRateModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FIncrementalRateModelMasterDomain>& Self,
        const Request::FGetIncrementalRateModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FIncrementalRateModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FIncrementalRateModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FIncrementalRateModelMaster>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRateName(Self->RateName);
        const auto Future = Self->Client->GetIncrementalRateModelMaster(
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

    TSharedPtr<FAsyncTask<FIncrementalRateModelMasterDomain::FGetTask>> FIncrementalRateModelMasterDomain::Get(
        Request::FGetIncrementalRateModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FIncrementalRateModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FIncrementalRateModelMasterDomain>& Self,
        const Request::FUpdateIncrementalRateModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FIncrementalRateModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FIncrementalRateModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FIncrementalRateModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRateName(Self->RateName);
        const auto Future = Self->Client->UpdateIncrementalRateModelMaster(
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

    TSharedPtr<FAsyncTask<FIncrementalRateModelMasterDomain::FUpdateTask>> FIncrementalRateModelMasterDomain::Update(
        Request::FUpdateIncrementalRateModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FIncrementalRateModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FIncrementalRateModelMasterDomain>& Self,
        const Request::FDeleteIncrementalRateModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FIncrementalRateModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FIncrementalRateModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FIncrementalRateModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRateName(Self->RateName);
        const auto Future = Self->Client->DeleteIncrementalRateModelMaster(
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

    TSharedPtr<FAsyncTask<FIncrementalRateModelMasterDomain::FDeleteTask>> FIncrementalRateModelMasterDomain::Delete(
        Request::FDeleteIncrementalRateModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FIncrementalRateModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RateName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (RateName.IsSet() ? *RateName : "null") + ":" +
            ChildType;
    }

    FString FIncrementalRateModelMasterDomain::CreateCacheKey(
        TOptional<FString> RateName
    )
    {
        return FString("") +
            (RateName.IsSet() ? *RateName : "null");
    }

    FIncrementalRateModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FIncrementalRateModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FIncrementalRateModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FIncrementalRateModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FIncrementalRateModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Exchange::Model::FIncrementalRateModelMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Exchange::Model::FIncrementalRateModelMaster>(
            Self->ParentKey,
            Gs2::Exchange::Domain::Model::FIncrementalRateModelMasterDomain::CreateCacheKey(
                Self->RateName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Exchange::Request::FGetIncrementalRateModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Exchange::Domain::Model::FIncrementalRateModelMasterDomain::CreateCacheKey(
                    Self->RateName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Exchange::Model::FIncrementalRateModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "incrementalRateModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Exchange::Model::FIncrementalRateModelMaster>(
                Self->ParentKey,
                Gs2::Exchange::Domain::Model::FIncrementalRateModelMasterDomain::CreateCacheKey(
                    Self->RateName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIncrementalRateModelMasterDomain::FModelTask>> FIncrementalRateModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FIncrementalRateModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FIncrementalRateModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Exchange::Model::FIncrementalRateModelMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Exchange::Model::FIncrementalRateModelMaster::TypeName,
            ParentKey,
            Gs2::Exchange::Domain::Model::FIncrementalRateModelMasterDomain::CreateCacheKey(
                RateName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Exchange::Model::FIncrementalRateModelMaster>(obj));
            }
        );
    }

    void FIncrementalRateModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Exchange::Model::FIncrementalRateModelMaster::TypeName,
            ParentKey,
            Gs2::Exchange::Domain::Model::FIncrementalRateModelMasterDomain::CreateCacheKey(
                RateName
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

