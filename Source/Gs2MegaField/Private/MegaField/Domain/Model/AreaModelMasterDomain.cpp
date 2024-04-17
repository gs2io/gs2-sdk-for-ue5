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

#include "MegaField/Domain/Model/AreaModelMaster.h"
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

    FAreaModelMasterDomain::FAreaModelMasterDomain(
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
            "AreaModelMaster"
        ))
    {
    }

    FAreaModelMasterDomain::FAreaModelMasterDomain(
        const FAreaModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AreaModelName(From.AreaModelName),
        ParentKey(From.ParentKey)
    {

    }

    FAreaModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FAreaModelMasterDomain>& Self,
        const Request::FGetAreaModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAreaModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FAreaModelMaster>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName);
        const auto Future = Self->Client->GetAreaModelMaster(
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
                const auto ParentKey = Gs2::MegaField::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "AreaModelMaster"
                );
                const auto Key = Gs2::MegaField::Domain::Model::FAreaModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::MegaField::Model::FAreaModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FAreaModelMasterDomain::FGetTask>> FAreaModelMasterDomain::Get(
        Request::FGetAreaModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FAreaModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FAreaModelMasterDomain>& Self,
        const Request::FUpdateAreaModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAreaModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FAreaModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName);
        const auto Future = Self->Client->UpdateAreaModelMaster(
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
                const auto ParentKey = Gs2::MegaField::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "AreaModelMaster"
                );
                const auto Key = Gs2::MegaField::Domain::Model::FAreaModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::MegaField::Model::FAreaModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FAreaModelMasterDomain::FUpdateTask>> FAreaModelMasterDomain::Update(
        Request::FUpdateAreaModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FAreaModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FAreaModelMasterDomain>& Self,
        const Request::FDeleteAreaModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAreaModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FAreaModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName);
        const auto Future = Self->Client->DeleteAreaModelMaster(
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
                const auto ParentKey = Gs2::MegaField::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "AreaModelMaster"
                );
                const auto Key = Gs2::MegaField::Domain::Model::FAreaModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::MegaField::Model::FAreaModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAreaModelMasterDomain::FDeleteTask>> FAreaModelMasterDomain::Delete(
        Request::FDeleteAreaModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FAreaModelMasterDomain::FCreateLayerModelMasterTask::FCreateLayerModelMasterTask(
        const TSharedPtr<FAreaModelMasterDomain>& Self,
        const Request::FCreateLayerModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAreaModelMasterDomain::FCreateLayerModelMasterTask::FCreateLayerModelMasterTask(
        const FCreateLayerModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelMasterDomain::FCreateLayerModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FLayerModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName);
        const auto Future = Self->Client->CreateLayerModelMaster(
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
                Self->Gs2->Cache->Put(
                    Gs2::MegaField::Model::FLayerModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::MegaField::Domain::Model::FLayerModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Request->GetAreaModelName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAreaModelMasterDomain::FCreateLayerModelMasterTask>> FAreaModelMasterDomain::CreateLayerModelMaster(
        Request::FCreateLayerModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateLayerModelMasterTask>>(this->AsShared(), Request);
    }

    Gs2::MegaField::Domain::Iterator::FDescribeLayerModelMastersIteratorPtr FAreaModelMasterDomain::LayerModelMasters(
    ) const
    {
        return MakeShared<Gs2::MegaField::Domain::Iterator::FDescribeLayerModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName,
            AreaModelName
        );
    }

    Gs2::Core::Domain::CallbackID FAreaModelMasterDomain::SubscribeLayerModelMasters(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::MegaField::Model::FLayerModelMaster::TypeName,
            Gs2::MegaField::Domain::Model::FAreaModelMasterDomain::CreateCacheParentKey(
                NamespaceName,
                AreaModelName,
                "LayerModelMaster"
            ),
            Callback
        );
    }

    void FAreaModelMasterDomain::UnsubscribeLayerModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::MegaField::Model::FLayerModelMaster::TypeName,
            Gs2::MegaField::Domain::Model::FAreaModelMasterDomain::CreateCacheParentKey(
                NamespaceName,
                AreaModelName,
                "LayerModelMaster"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::MegaField::Domain::Model::FLayerModelMasterDomain> FAreaModelMasterDomain::LayerModelMaster(
        const FString LayerModelName
    )
    {
        return MakeShared<Gs2::MegaField::Domain::Model::FLayerModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            AreaModelName,
            LayerModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(LayerModelName)
        );
    }

    FString FAreaModelMasterDomain::CreateCacheParentKey(
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

    FString FAreaModelMasterDomain::CreateCacheKey(
        TOptional<FString> AreaModelName
    )
    {
        return FString("") +
            (AreaModelName.IsSet() ? *AreaModelName : "null");
    }

    FAreaModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FAreaModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FAreaModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FAreaModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::MegaField::Model::FAreaModelMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::MegaField::Model::FAreaModelMaster>(
            Self->ParentKey,
            Gs2::MegaField::Domain::Model::FAreaModelMasterDomain::CreateCacheKey(
                Self->AreaModelName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::MegaField::Request::FGetAreaModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::MegaField::Domain::Model::FAreaModelMasterDomain::CreateCacheKey(
                    Self->AreaModelName
                );
                Self->Gs2->Cache->Put(
                    Gs2::MegaField::Model::FAreaModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "areaModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::MegaField::Model::FAreaModelMaster>(
                Self->ParentKey,
                Gs2::MegaField::Domain::Model::FAreaModelMasterDomain::CreateCacheKey(
                    Self->AreaModelName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAreaModelMasterDomain::FModelTask>> FAreaModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAreaModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FAreaModelMasterDomain::Subscribe(
        TFunction<void(Gs2::MegaField::Model::FAreaModelMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::MegaField::Model::FAreaModelMaster::TypeName,
            ParentKey,
            Gs2::MegaField::Domain::Model::FAreaModelMasterDomain::CreateCacheKey(
                AreaModelName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::MegaField::Model::FAreaModelMaster>(obj));
            }
        );
    }

    void FAreaModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::MegaField::Model::FAreaModelMaster::TypeName,
            ParentKey,
            Gs2::MegaField::Domain::Model::FAreaModelMasterDomain::CreateCacheKey(
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

