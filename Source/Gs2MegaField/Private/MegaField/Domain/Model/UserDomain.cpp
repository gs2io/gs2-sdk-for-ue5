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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "MegaField/Domain/Model/User.h"
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

namespace Gs2::MegaField::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const MegaField::Domain::FGs2MegaFieldDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::MegaField::FGs2MegaFieldRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::MegaField::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FFetchPositionFromSystemTask::FFetchPositionFromSystemTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FFetchPositionFromSystemRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FFetchPositionFromSystemTask::FFetchPositionFromSystemTask(
        const FFetchPositionFromSystemTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FFetchPositionFromSystemTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->FetchPositionFromSystem(
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
                    Self->Gs2->Cache->Put(
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
                    Self->Gs2,
                    Self->Service,
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
            Self->Gs2->Cache->Put(
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

    TSharedPtr<FAsyncTask<FUserDomain::FFetchPositionFromSystemTask>> FUserDomain::FetchPositionFromSystem(
        Request::FFetchPositionFromSystemRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FFetchPositionFromSystemTask>>(this->AsShared(), Request);
    }

    FUserDomain::FNearUserIdsFromSystemTask::FNearUserIdsFromSystemTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FNearUserIdsFromSystemRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FNearUserIdsFromSystemTask::FNearUserIdsFromSystemTask(
        const FNearUserIdsFromSystemTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FNearUserIdsFromSystemTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->NearUserIdsFromSystem(
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
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::MegaField::Domain::Model::FSpatialDomain>(
                    Self->Gs2,
                    Self->Service,
                    Request->GetNamespaceName(),
                    (*ResultModel->GetItems())[i],
                    RequestModel->GetAreaModelName(),
                    RequestModel->GetLayerModelName()
                )
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FNearUserIdsFromSystemTask>> FUserDomain::NearUserIdsFromSystem(
        Request::FNearUserIdsFromSystemRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FNearUserIdsFromSystemTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain> FUserDomain::Spatial(
        const FString AreaModelName,
        const FString LayerModelName
    )
    {
        return MakeShared<Gs2::MegaField::Domain::Model::FSpatialDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            AreaModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(AreaModelName),
            LayerModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(LayerModelName)
        );
    }

    FString FUserDomain::CreateCacheParentKey(
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

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

