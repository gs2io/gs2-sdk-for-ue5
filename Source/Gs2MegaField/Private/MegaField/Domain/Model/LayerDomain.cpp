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

#include "MegaField/Domain/Model/Layer.h"
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
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::MegaField::Domain::Model
{

    FLayerDomain::FLayerDomain(
        const Core::Domain::FGs2Ptr Gs2,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> AreaModelName,
        const TOptional<FString> LayerModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::MegaField::FGs2MegaFieldRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AreaModelName(AreaModelName),
        LayerModelName(LayerModelName),
        ParentKey(Gs2::MegaField::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "Layer"
        ))
    {
    }

    FLayerDomain::FLayerDomain(
        const FLayerDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AreaModelName(From.AreaModelName),
        LayerModelName(From.LayerModelName),
        ParentKey(From.ParentKey)
    {

    }

    FString FLayerDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> AreaModelName,
        TOptional<FString> LayerModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (AreaModelName.IsSet() ? *AreaModelName : "null") + ":" +
            (LayerModelName.IsSet() ? *LayerModelName : "null") + ":" +
            ChildType;
    }

    FString FLayerDomain::CreateCacheKey(
        TOptional<FString> AreaModelName,
        TOptional<FString> LayerModelName
    )
    {
        return FString("") +
            (AreaModelName.IsSet() ? *AreaModelName : "null") + ":" + 
            (LayerModelName.IsSet() ? *LayerModelName : "null");
    }

    FLayerDomain::FModelTask::FModelTask(
        const TSharedPtr<FLayerDomain> Self
    ): Self(Self)
    {

    }

    FLayerDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FLayerDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FLayer>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::MegaField::Model::FLayer> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::MegaField::Model::FLayer>(
            Self->ParentKey,
            Gs2::MegaField::Domain::Model::FLayerDomain::CreateCacheKey(
                Self->AreaModelName,
                Self->LayerModelName
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLayerDomain::FModelTask>> FLayerDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FLayerDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FLayerDomain::Subscribe(
        TFunction<void(Gs2::MegaField::Model::FLayerPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::MegaField::Model::FLayer::TypeName,
            ParentKey,
            Gs2::MegaField::Domain::Model::FLayerDomain::CreateCacheKey(
                AreaModelName,
                LayerModelName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::MegaField::Model::FLayer>(obj));
            }
        );
    }

    void FLayerDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::MegaField::Model::FLayer::TypeName,
            ParentKey,
            Gs2::MegaField::Domain::Model::FLayerDomain::CreateCacheKey(
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

