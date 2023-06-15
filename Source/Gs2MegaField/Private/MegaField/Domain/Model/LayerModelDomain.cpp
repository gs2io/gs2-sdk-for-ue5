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

#include "MegaField/Domain/Model/LayerModel.h"
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

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::MegaField::Domain::Model
{

    FLayerModelDomain::FLayerModelDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> AreaModelName,
        const TOptional<FString> LayerModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::MegaField::FGs2MegaFieldRestClient>(Session)),
        NamespaceName(NamespaceName),
        AreaModelName(AreaModelName),
        LayerModelName(LayerModelName),
        ParentKey(Gs2::MegaField::Domain::Model::FAreaModelDomain::CreateCacheParentKey(
            NamespaceName,
            AreaModelName,
            "LayerModel"
        ))
    {
    }

    FLayerModelDomain::FLayerModelDomain(
        const FLayerModelDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FLayerModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FLayerModelDomain> Self,
        const Request::FGetLayerModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLayerModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLayerModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FLayerModel>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName)
            ->WithLayerModelName(Self->LayerModelName);
        const auto Future = Self->Client->GetLayerModel(
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
                const auto ParentKey = Gs2::MegaField::Domain::Model::FAreaModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->AreaModelName,
                    "LayerModel"
                );
                const auto Key = Gs2::MegaField::Domain::Model::FLayerModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::MegaField::Model::FLayerModel::TypeName,
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

    TSharedPtr<FAsyncTask<FLayerModelDomain::FGetTask>> FLayerModelDomain::Get(
        Request::FGetLayerModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FLayerModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> AreaModelName,
        TOptional<FString> LayerModelName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (AreaModelName.IsSet() ? *AreaModelName : "null") + ":" +
            (LayerModelName.IsSet() ? *LayerModelName : "null") + ":" +
            ChildType;
    }

    FString FLayerModelDomain::CreateCacheKey(
        TOptional<FString> LayerModelName
    )
    {
        return FString() +
            (LayerModelName.IsSet() ? *LayerModelName : "null");
    }

    FLayerModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FLayerModelDomain> Self
    ): Self(Self)
    {

    }

    FLayerModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FLayerModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FLayerModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::MegaField::Model::FLayerModel> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::MegaField::Model::FLayerModel>(
            Self->ParentKey,
            Gs2::MegaField::Domain::Model::FLayerModelDomain::CreateCacheKey(
                Self->LayerModelName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::MegaField::Request::FGetLayerModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::MegaField::Domain::Model::FLayerModelDomain::CreateCacheKey(
                    Self->LayerModelName
                );
                Self->Cache->Put(
                    Gs2::MegaField::Model::FLayerModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "layerModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::MegaField::Model::FLayerModel>(
                Self->ParentKey,
                Gs2::MegaField::Domain::Model::FLayerModelDomain::CreateCacheKey(
                    Self->LayerModelName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLayerModelDomain::FModelTask>> FLayerModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FLayerModelDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

