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

#include "Mission/Domain/Model/CounterModel.h"
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

    FCounterModelDomain::FCounterModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Mission::Domain::FGs2MissionDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> CounterName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Mission::FGs2MissionRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        CounterName(CounterName),
        ParentKey(Gs2::Mission::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CounterModel"
        ))
    {
    }

    FCounterModelDomain::FCounterModelDomain(
        const FCounterModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        CounterName(From.CounterName),
        ParentKey(From.ParentKey)
    {

    }

    FCounterModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FCounterModelDomain>& Self,
        const Request::FGetCounterModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCounterModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FCounterModel>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCounterName(Self->CounterName);
        const auto Future = Self->Client->GetCounterModel(
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

    TSharedPtr<FAsyncTask<FCounterModelDomain::FGetTask>> FCounterModelDomain::Get(
        Request::FGetCounterModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FCounterModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> CounterName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (CounterName.IsSet() ? *CounterName : "null") + ":" +
            ChildType;
    }

    FString FCounterModelDomain::CreateCacheKey(
        TOptional<FString> CounterName
    )
    {
        return FString("") +
            (CounterName.IsSet() ? *CounterName : "null");
    }

    FCounterModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FCounterModelDomain> Self
    ): Self(Self)
    {

    }

    FCounterModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FCounterModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Mission::Model::FCounterModel> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Mission::Model::FCounterModel>(
            Self->ParentKey,
            Gs2::Mission::Domain::Model::FCounterModelDomain::CreateCacheKey(
                Self->CounterName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Mission::Request::FGetCounterModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Mission::Domain::Model::FCounterModelDomain::CreateCacheKey(
                    Self->CounterName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Mission::Model::FCounterModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "counterModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Mission::Model::FCounterModel>(
                Self->ParentKey,
                Gs2::Mission::Domain::Model::FCounterModelDomain::CreateCacheKey(
                    Self->CounterName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCounterModelDomain::FModelTask>> FCounterModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCounterModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCounterModelDomain::Subscribe(
        TFunction<void(Gs2::Mission::Model::FCounterModelPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Mission::Model::FCounterModel::TypeName,
            ParentKey,
            Gs2::Mission::Domain::Model::FCounterModelDomain::CreateCacheKey(
                CounterName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Mission::Model::FCounterModel>(obj));
            }
        );
    }

    void FCounterModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Mission::Model::FCounterModel::TypeName,
            ParentKey,
            Gs2::Mission::Domain::Model::FCounterModelDomain::CreateCacheKey(
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

