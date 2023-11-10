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

#include "Deploy/Domain/Model/Resource.h"
#include "Deploy/Domain/Model/Stack.h"
#include "Deploy/Domain/Model/Resource.h"
#include "Deploy/Domain/Model/Event.h"
#include "Deploy/Domain/Model/Output.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Deploy::Domain::Model
{

    FResourceDomain::FResourceDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Deploy::Domain::FGs2DeployDomainPtr& Service,
        const TOptional<FString> StackName,
        const TOptional<FString> ResourceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Deploy::FGs2DeployRestClient>(Gs2->RestSession)),
        StackName(StackName),
        ResourceName(ResourceName),
        ParentKey(Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheParentKey(
            StackName,
            "Resource"
        ))
    {
    }

    FResourceDomain::FResourceDomain(
        const FResourceDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        StackName(From.StackName),
        ResourceName(From.ResourceName),
        ParentKey(From.ParentKey)
    {

    }

    FResourceDomain::FGetTask::FGetTask(
        const TSharedPtr<FResourceDomain>& Self,
        const Request::FGetResourceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FResourceDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FResourceDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FResource>> Result
    )
    {
        Request
            ->WithStackName(Self->StackName)
            ->WithResourceName(Self->ResourceName);
        const auto Future = Self->Client->GetResource(
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
                const auto ParentKey = Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheParentKey(
                    Self->StackName,
                    "Resource"
                );
                const auto Key = Gs2::Deploy::Domain::Model::FResourceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Deploy::Model::FResource::TypeName,
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

    TSharedPtr<FAsyncTask<FResourceDomain::FGetTask>> FResourceDomain::Get(
        Request::FGetResourceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FResourceDomain::CreateCacheParentKey(
        TOptional<FString> StackName,
        TOptional<FString> ResourceName,
        FString ChildType
    )
    {
        return FString("") +
            (StackName.IsSet() ? *StackName : "null") + ":" +
            (ResourceName.IsSet() ? *ResourceName : "null") + ":" +
            ChildType;
    }

    FString FResourceDomain::CreateCacheKey(
        TOptional<FString> ResourceName
    )
    {
        return FString("") +
            (ResourceName.IsSet() ? *ResourceName : "null");
    }

    FResourceDomain::FModelTask::FModelTask(
        const TSharedPtr<FResourceDomain> Self
    ): Self(Self)
    {

    }

    FResourceDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FResourceDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FResource>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Deploy::Model::FResource> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Deploy::Model::FResource>(
            Self->ParentKey,
            Gs2::Deploy::Domain::Model::FResourceDomain::CreateCacheKey(
                Self->ResourceName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Deploy::Request::FGetResourceRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Deploy::Domain::Model::FResourceDomain::CreateCacheKey(
                    Self->ResourceName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Deploy::Model::FResource::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "resource")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Deploy::Model::FResource>(
                Self->ParentKey,
                Gs2::Deploy::Domain::Model::FResourceDomain::CreateCacheKey(
                    Self->ResourceName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FResourceDomain::FModelTask>> FResourceDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FResourceDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FResourceDomain::Subscribe(
        TFunction<void(Gs2::Deploy::Model::FResourcePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Deploy::Model::FResource::TypeName,
            ParentKey,
            Gs2::Deploy::Domain::Model::FResourceDomain::CreateCacheKey(
                ResourceName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Deploy::Model::FResource>(obj));
            }
        );
    }

    void FResourceDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Deploy::Model::FResource::TypeName,
            ParentKey,
            Gs2::Deploy::Domain::Model::FResourceDomain::CreateCacheKey(
                ResourceName
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

