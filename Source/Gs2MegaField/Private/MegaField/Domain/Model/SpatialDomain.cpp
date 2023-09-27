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

#include "MegaField/Domain/Model/Spatial.h"
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

    FSpatialDomain::FSpatialDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
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
        UserId(UserId),
        AreaModelName(AreaModelName),
        LayerModelName(LayerModelName),
        ParentKey(Gs2::MegaField::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Spatial"
        ))
    {
    }

    FSpatialDomain::FSpatialDomain(
        const FSpatialDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        AreaModelName(From.AreaModelName),
        LayerModelName(From.LayerModelName),
        ParentKey(From.ParentKey)
    {

    }

    FSpatialDomain::FPutPositionTask::FPutPositionTask(
        const TSharedPtr<FSpatialDomain> Self,
        const Request::FPutPositionByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSpatialDomain::FPutPositionTask::FPutPositionTask(
        const FPutPositionTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSpatialDomain::FPutPositionTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithAreaModelName(Self->AreaModelName)
            ->WithLayerModelName(Self->LayerModelName);
        const auto Future = Self->Client->PutPositionByUserId(
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
                const auto ParentKey = Gs2::MegaField::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Spatial"
                );
                const auto Key = Gs2::MegaField::Domain::Model::FSpatialDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetAreaModelName(),
                    ResultModel->GetItem()->GetLayerModelName()
                );
                Self->Cache->Put(
                    Gs2::MegaField::Model::FSpatial::TypeName,
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

    TSharedPtr<FAsyncTask<FSpatialDomain::FPutPositionTask>> FSpatialDomain::PutPosition(
        Request::FPutPositionByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPutPositionTask>>(this->AsShared(), Request);
    }

    FSpatialDomain::FActionTask::FActionTask(
        const TSharedPtr<FSpatialDomain> Self,
        const Request::FActionByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSpatialDomain::FActionTask::FActionTask(
        const FActionTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSpatialDomain::FActionTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithAreaModelName(Self->AreaModelName)
            ->WithLayerModelName(Self->LayerModelName);
        const auto Future = Self->Client->ActionByUserId(
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
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::MegaField::Domain::Model::FUserDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        "Spatial"
                    );
                    const auto Key = Gs2::MegaField::Domain::Model::FSpatialDomain::CreateCacheKey(
                        Item->GetAreaModelName(),
                        Item->GetLayerModelName()
                    );
                    Self->Cache->Put(
                        Gs2::MegaField::Model::FSpatial::TypeName,
                        ParentKey,
                        Key,
                        Item,
                        FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            }
        }
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::MegaField::Domain::Model::FSpatialDomain>(
                    Self->Cache,
                    Self->JobQueueDomain,
                    Self->StampSheetConfiguration,
                    Self->Session,
                    Request->GetNamespaceName(),
                    (*ResultModel->GetItems())[i]->GetUserId(),
                    (*ResultModel->GetItems())[i]->GetAreaModelName(),
                    (*ResultModel->GetItems())[i]->GetLayerModelName()
                )
            );
            const auto ParentKey = Gs2::MegaField::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                "Spatial"
            );
            const auto Key = Gs2::MegaField::Domain::Model::FSpatialDomain::CreateCacheKey(
                (*ResultModel->GetItems())[i]->GetAreaModelName(),
                (*ResultModel->GetItems())[i]->GetLayerModelName()
            );
            Self->Cache->Put(
                Gs2::MegaField::Model::FSpatial::TypeName,
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSpatialDomain::FActionTask>> FSpatialDomain::Action(
        Request::FActionByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FActionTask>>(this->AsShared(), Request);
    }

    FString FSpatialDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> AreaModelName,
        TOptional<FString> LayerModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (AreaModelName.IsSet() ? *AreaModelName : "null") + ":" +
            (LayerModelName.IsSet() ? *LayerModelName : "null") + ":" +
            ChildType;
    }

    FString FSpatialDomain::CreateCacheKey(
        TOptional<FString> AreaModelName,
        TOptional<FString> LayerModelName
    )
    {
        return FString("") +
            (AreaModelName.IsSet() ? *AreaModelName : "null") + ":" + 
            (LayerModelName.IsSet() ? *LayerModelName : "null");
    }

    FSpatialDomain::FModelTask::FModelTask(
        const TSharedPtr<FSpatialDomain> Self
    ): Self(Self)
    {

    }

    FSpatialDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSpatialDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FSpatial>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::MegaField::Model::FSpatial> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::MegaField::Model::FSpatial>(
            Self->ParentKey,
            Gs2::MegaField::Domain::Model::FSpatialDomain::CreateCacheKey(
                Self->AreaModelName,
                Self->LayerModelName
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSpatialDomain::FModelTask>> FSpatialDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSpatialDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FSpatialDomain::Subscribe(
        TFunction<void(Gs2::MegaField::Model::FSpatialPtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::MegaField::Model::FSpatial::TypeName,
            ParentKey,
            Gs2::MegaField::Domain::Model::FSpatialDomain::CreateCacheKey(
                AreaModelName,
                LayerModelName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::MegaField::Model::FSpatial>(obj));
            }
        );
    }

    void FSpatialDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::MegaField::Model::FSpatial::TypeName,
            ParentKey,
            Gs2::MegaField::Domain::Model::FSpatialDomain::CreateCacheKey(
                AreaModelName,
                LayerModelName
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

