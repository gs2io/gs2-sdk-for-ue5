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

#include "MegaField/Domain/Model/AreaModel.h"
#include "MegaField/Domain/Model/Namespace.h"
#include "MegaField/Domain/Model/AreaModel.h"
#include "MegaField/Domain/Model/AreaModelMaster.h"
#include "MegaField/Domain/Model/LayerModel.h"
#include "MegaField/Domain/Model/LayerModelMaster.h"
#include "MegaField/Domain/Model/CurrentFieldMaster.h"
#include "MegaField/Domain/Model/User.h"
#include "MegaField/Domain/Model/UserAccessToken.h"
#include "MegaField/Domain/Model/Spatial.h"
#include "MegaField/Domain/Model/SpatialAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::MegaField::Domain::Model
{

    FAreaModelDomain::FAreaModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const MegaField::Domain::FGs2MegaFieldDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> AreaModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::MegaField::FGs2MegaFieldRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AreaModelName(AreaModelName),
        ParentKey(Gs2::MegaField::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "AreaModel"
        ))
    {
    }

    FAreaModelDomain::FAreaModelDomain(
        const FAreaModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AreaModelName(From.AreaModelName),
        ParentKey(From.ParentKey)
    {

    }

    FAreaModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FAreaModelDomain>& Self,
        const Request::FGetAreaModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAreaModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FAreaModel>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName);
        const auto Future = Self->Client->GetAreaModel(
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

    TSharedPtr<FAsyncTask<FAreaModelDomain::FGetTask>> FAreaModelDomain::Get(
        Request::FGetAreaModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    Gs2::MegaField::Domain::Iterator::FDescribeLayerModelsIteratorPtr FAreaModelDomain::LayerModels(
    ) const
    {
        return MakeShared<Gs2::MegaField::Domain::Iterator::FDescribeLayerModelsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AreaModelName
        );
    }

    Gs2::Core::Domain::CallbackID FAreaModelDomain::SubscribeLayerModels(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::MegaField::Model::FLayerModel::TypeName,
            Gs2::MegaField::Domain::Model::FAreaModelDomain::CreateCacheParentKey(
                NamespaceName,
                AreaModelName,
                "LayerModel"
            ),
            Callback
        );
    }

    void FAreaModelDomain::UnsubscribeLayerModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::MegaField::Model::FLayerModel::TypeName,
            Gs2::MegaField::Domain::Model::FAreaModelDomain::CreateCacheParentKey(
                NamespaceName,
                AreaModelName,
                "LayerModel"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::MegaField::Domain::Model::FLayerModelDomain> FAreaModelDomain::LayerModel(
        const FString LayerModelName
    )
    {
        return MakeShared<Gs2::MegaField::Domain::Model::FLayerModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            AreaModelName,
            LayerModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(LayerModelName)
        );
    }

    FString FAreaModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> AreaModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (AreaModelName.IsSet() ? *AreaModelName : "null") + ":" +
            ChildType;
    }

    FString FAreaModelDomain::CreateCacheKey(
        TOptional<FString> AreaModelName
    )
    {
        return FString("") +
            (AreaModelName.IsSet() ? *AreaModelName : "null");
    }

    FAreaModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FAreaModelDomain> Self
    ): Self(Self)
    {

    }

    FAreaModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FAreaModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::MegaField::Model::FAreaModel> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::MegaField::Model::FAreaModel>(
            Self->ParentKey,
            Gs2::MegaField::Domain::Model::FAreaModelDomain::CreateCacheKey(
                Self->AreaModelName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::MegaField::Request::FGetAreaModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::MegaField::Domain::Model::FAreaModelDomain::CreateCacheKey(
                    Self->AreaModelName
                );
                Self->Gs2->Cache->Put(
                    Gs2::MegaField::Model::FAreaModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "areaModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::MegaField::Model::FAreaModel>(
                Self->ParentKey,
                Gs2::MegaField::Domain::Model::FAreaModelDomain::CreateCacheKey(
                    Self->AreaModelName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAreaModelDomain::FModelTask>> FAreaModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAreaModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FAreaModelDomain::Subscribe(
        TFunction<void(Gs2::MegaField::Model::FAreaModelPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::MegaField::Model::FAreaModel::TypeName,
            ParentKey,
            Gs2::MegaField::Domain::Model::FAreaModelDomain::CreateCacheKey(
                AreaModelName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::MegaField::Model::FAreaModel>(obj));
            }
        );
    }

    void FAreaModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::MegaField::Model::FAreaModel::TypeName,
            ParentKey,
            Gs2::MegaField::Domain::Model::FAreaModelDomain::CreateCacheKey(
                AreaModelName
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

