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

#include "Enhance/Domain/Model/UnleashRateModel.h"
#include "Enhance/Domain/Model/Namespace.h"
#include "Enhance/Domain/Model/RateModel.h"
#include "Enhance/Domain/Model/RateModelMaster.h"
#include "Enhance/Domain/Model/UnleashRateModel.h"
#include "Enhance/Domain/Model/UnleashRateModelMaster.h"
#include "Enhance/Domain/Model/Enhance.h"
#include "Enhance/Domain/Model/EnhanceAccessToken.h"
#include "Enhance/Domain/Model/Progress.h"
#include "Enhance/Domain/Model/ProgressAccessToken.h"
#include "Enhance/Domain/Model/CurrentRateMaster.h"
#include "Enhance/Domain/Model/User.h"
#include "Enhance/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Enhance::Domain::Model
{

    FUnleashRateModelDomain::FUnleashRateModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Enhance::Domain::FGs2EnhanceDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RateName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Enhance::FGs2EnhanceRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        RateName(RateName),
        ParentKey(Gs2::Enhance::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "UnleashRateModel"
        ))
    {
    }

    FUnleashRateModelDomain::FUnleashRateModelDomain(
        const FUnleashRateModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RateName(From.RateName),
        ParentKey(From.ParentKey)
    {

    }

    FUnleashRateModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FUnleashRateModelDomain>& Self,
        const Request::FGetUnleashRateModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUnleashRateModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUnleashRateModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FUnleashRateModel>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRateName(Self->RateName);
        const auto Future = Self->Client->GetUnleashRateModel(
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
                const auto ParentKey = Gs2::Enhance::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "UnleashRateModel"
                );
                const auto Key = Gs2::Enhance::Domain::Model::FUnleashRateModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Enhance::Model::FUnleashRateModel::TypeName,
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

    TSharedPtr<FAsyncTask<FUnleashRateModelDomain::FGetTask>> FUnleashRateModelDomain::Get(
        Request::FGetUnleashRateModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FUnleashRateModelDomain::CreateCacheParentKey(
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

    FString FUnleashRateModelDomain::CreateCacheKey(
        TOptional<FString> RateName
    )
    {
        return FString("") +
            (RateName.IsSet() ? *RateName : "null");
    }

    FUnleashRateModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FUnleashRateModelDomain> Self
    ): Self(Self)
    {

    }

    FUnleashRateModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FUnleashRateModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FUnleashRateModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Enhance::Model::FUnleashRateModel> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Enhance::Model::FUnleashRateModel>(
            Self->ParentKey,
            Gs2::Enhance::Domain::Model::FUnleashRateModelDomain::CreateCacheKey(
                Self->RateName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Enhance::Request::FGetUnleashRateModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Enhance::Domain::Model::FUnleashRateModelDomain::CreateCacheKey(
                    Self->RateName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Enhance::Model::FUnleashRateModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "unleashRateModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Enhance::Model::FUnleashRateModel>(
                Self->ParentKey,
                Gs2::Enhance::Domain::Model::FUnleashRateModelDomain::CreateCacheKey(
                    Self->RateName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUnleashRateModelDomain::FModelTask>> FUnleashRateModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FUnleashRateModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FUnleashRateModelDomain::Subscribe(
        TFunction<void(Gs2::Enhance::Model::FUnleashRateModelPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Enhance::Model::FUnleashRateModel::TypeName,
            ParentKey,
            Gs2::Enhance::Domain::Model::FUnleashRateModelDomain::CreateCacheKey(
                RateName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Enhance::Model::FUnleashRateModel>(obj));
            }
        );
    }

    void FUnleashRateModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Enhance::Model::FUnleashRateModel::TypeName,
            ParentKey,
            Gs2::Enhance::Domain::Model::FUnleashRateModelDomain::CreateCacheKey(
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

