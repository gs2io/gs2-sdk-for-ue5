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

#include "MegaField/Domain/Model/LayerModelMaster.h"
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

    FLayerModelMasterDomain::FLayerModelMasterDomain(
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
        ParentKey(Gs2::MegaField::Domain::Model::FAreaModelMasterDomain::CreateCacheParentKey(
            NamespaceName,
            AreaModelName,
            "LayerModelMaster"
        ))
    {
    }

    FLayerModelMasterDomain::FLayerModelMasterDomain(
        const FLayerModelMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FLayerModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FLayerModelMasterDomain> Self,
        const Request::FGetLayerModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLayerModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLayerModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FLayerModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName)
            ->WithLayerModelName(Self->LayerModelName);
        const auto Future = Self->Client->GetLayerModelMaster(
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
                const auto ParentKey = Gs2::MegaField::Domain::Model::FAreaModelMasterDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->AreaModelName,
                    "LayerModelMaster"
                );
                const auto Key = Gs2::MegaField::Domain::Model::FLayerModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::MegaField::Model::FLayerModelMaster>(
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

    TSharedPtr<FAsyncTask<FLayerModelMasterDomain::FGetTask>> FLayerModelMasterDomain::Get(
        Request::FGetLayerModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FLayerModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FLayerModelMasterDomain> Self,
        const Request::FUpdateLayerModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLayerModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLayerModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FLayerModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName)
            ->WithLayerModelName(Self->LayerModelName);
        const auto Future = Self->Client->UpdateLayerModelMaster(
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
                const auto ParentKey = Gs2::MegaField::Domain::Model::FAreaModelMasterDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->AreaModelName,
                    "LayerModelMaster"
                );
                const auto Key = Gs2::MegaField::Domain::Model::FLayerModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::MegaField::Model::FLayerModelMaster>(
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

    TSharedPtr<FAsyncTask<FLayerModelMasterDomain::FUpdateTask>> FLayerModelMasterDomain::Update(
        Request::FUpdateLayerModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FLayerModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FLayerModelMasterDomain> Self,
        const Request::FDeleteLayerModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLayerModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLayerModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FLayerModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName)
            ->WithLayerModelName(Self->LayerModelName);
        const auto Future = Self->Client->DeleteLayerModelMaster(
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
                const auto ParentKey = Gs2::MegaField::Domain::Model::FAreaModelMasterDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->AreaModelName,
                    "LayerModelMaster"
                );
                const auto Key = Gs2::MegaField::Domain::Model::FLayerModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete<Gs2::MegaField::Model::FLayerModelMaster>(ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLayerModelMasterDomain::FDeleteTask>> FLayerModelMasterDomain::Delete(
        Request::FDeleteLayerModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FLayerModelMasterDomain::CreateCacheParentKey(
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

    FString FLayerModelMasterDomain::CreateCacheKey(
        TOptional<FString> LayerModelName
    )
    {
        return FString() +
            (LayerModelName.IsSet() ? *LayerModelName : "null");
    }

    FLayerModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FLayerModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FLayerModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FLayerModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FLayerModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::MegaField::Model::FLayerModelMaster>(
            Self->ParentKey,
            Gs2::MegaField::Domain::Model::FLayerModelMasterDomain::CreateCacheKey(
                Self->LayerModelName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::MegaField::Request::FGetLayerModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "layerModelMaster")
                    {
                        Self->Cache->Delete<Gs2::MegaField::Model::FLayerModelMaster>(
                            Self->ParentKey,
                            Gs2::MegaField::Domain::Model::FLayerModelMasterDomain::CreateCacheKey(
                                Self->LayerModelName
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
            Value = Self->Cache->Get<Gs2::MegaField::Model::FLayerModelMaster>(
                Self->ParentKey,
                Gs2::MegaField::Domain::Model::FLayerModelMasterDomain::CreateCacheKey(
                    Self->LayerModelName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLayerModelMasterDomain::FModelTask>> FLayerModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FLayerModelMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

