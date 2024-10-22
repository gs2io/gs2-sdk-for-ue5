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

#include "Showcase/Domain/Model/DisplayItemMaster.h"
#include "Showcase/Domain/Model/Namespace.h"
#include "Showcase/Domain/Model/SalesItemMaster.h"
#include "Showcase/Domain/Model/SalesItemGroupMaster.h"
#include "Showcase/Domain/Model/ShowcaseMaster.h"
#include "Showcase/Domain/Model/CurrentShowcaseMaster.h"
#include "Showcase/Domain/Model/Showcase.h"
#include "Showcase/Domain/Model/ShowcaseAccessToken.h"
#include "Showcase/Domain/Model/DisplayItem.h"
#include "Showcase/Domain/Model/DisplayItemAccessToken.h"
#include "Showcase/Domain/Model/RandomShowcaseMaster.h"
#include "Showcase/Domain/Model/RandomShowcase.h"
#include "Showcase/Domain/Model/RandomShowcaseAccessToken.h"
#include "Showcase/Domain/Model/User.h"
#include "Showcase/Domain/Model/UserAccessToken.h"
#include "Showcase/Domain/Model/RandomShowcaseStatus.h"
#include "Showcase/Domain/Model/RandomShowcaseStatusAccessToken.h"
#include "Showcase/Domain/Model/RandomDisplayItem.h"
#include "Showcase/Domain/Model/RandomDisplayItemAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Showcase::Domain::Model
{

    FDisplayItemMasterDomain::FDisplayItemMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::Showcase::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "DisplayItemMaster"
        ))
    {
    }

    FDisplayItemMasterDomain::FDisplayItemMasterDomain(
        const FDisplayItemMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FString FDisplayItemMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FDisplayItemMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FDisplayItemMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FDisplayItemMasterDomain> Self
    ): Self(Self)
    {

    }

    FDisplayItemMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDisplayItemMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FDisplayItemMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Showcase::Model::FDisplayItemMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Showcase::Model::FDisplayItemMaster>(
            Self->ParentKey,
            Gs2::Showcase::Domain::Model::FDisplayItemMasterDomain::CreateCacheKey(
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDisplayItemMasterDomain::FModelTask>> FDisplayItemMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDisplayItemMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FDisplayItemMasterDomain::Subscribe(
        TFunction<void(Gs2::Showcase::Model::FDisplayItemMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Showcase::Model::FDisplayItemMaster::TypeName,
            ParentKey,
            Gs2::Showcase::Domain::Model::FDisplayItemMasterDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Showcase::Model::FDisplayItemMaster>(obj));
            }
        );
    }

    void FDisplayItemMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Showcase::Model::FDisplayItemMaster::TypeName,
            ParentKey,
            Gs2::Showcase::Domain::Model::FDisplayItemMasterDomain::CreateCacheKey(
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

