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

#include "Script/Domain/Model/Namespace.h"
#include "Script/Domain/Model/Namespace.h"
#include "Script/Domain/Model/Script.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Script::Domain::Model
{

    FNamespaceDomain::FNamespaceDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Script::Domain::FGs2ScriptDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Script::FGs2ScriptRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey("script:Namespace")
    {
    }

    FNamespaceDomain::FNamespaceDomain(
        const FNamespaceDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FGetNamespaceStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const FGetStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespaceStatus(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetStatus().IsSet())
            {
                Self->Status = Domain->Status = ResultModel->GetStatus();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetStatusTask>> FNamespaceDomain::GetStatus(
        Request::FGetNamespaceStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetStatusTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FGetTask::FGetTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FGetNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Script::Model::FNamespace>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetTask>> FNamespaceDomain::Get(
        Request::FGetNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FUpdateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FUpdateTask>> FNamespaceDomain::Update(
        Request::FUpdateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FDeleteNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DeleteNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDeleteTask>> FNamespaceDomain::Delete(
        Request::FDeleteNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateScriptTask::FCreateScriptTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateScriptRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateScriptTask::FCreateScriptTask(
        const FCreateScriptTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateScriptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FScriptDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateScript(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        auto Domain = MakeShared<Gs2::Script::Domain::Model::FScriptDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateScriptTask>> FNamespaceDomain::CreateScript(
        Request::FCreateScriptRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateScriptTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateScriptFromGitHubTask::FCreateScriptFromGitHubTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateScriptFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateScriptFromGitHubTask::FCreateScriptFromGitHubTask(
        const FCreateScriptFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateScriptFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FScriptDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateScriptFromGitHub(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        auto Domain = MakeShared<Gs2::Script::Domain::Model::FScriptDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateScriptFromGitHubTask>> FNamespaceDomain::CreateScriptFromGitHub(
        Request::FCreateScriptFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateScriptFromGitHubTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FInvokeScriptTask::FInvokeScriptTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FInvokeScriptRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FInvokeScriptTask::FInvokeScriptTask(
        const FInvokeScriptTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FInvokeScriptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FNamespaceDomain>> Result
    )
    {
        const auto Future = Self->Client->InvokeScript(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetCode().IsSet())
            {
                Self->Code = Domain->Code = ResultModel->GetCode();
            }
            if (ResultModel->GetResult().IsSet())
            {
                Self->Result = Domain->Result = ResultModel->GetResult();
            }
            if (ResultModel->GetExecuteTime().IsSet())
            {
                Self->ExecuteTime = Domain->ExecuteTime = ResultModel->GetExecuteTime();
            }
            if (ResultModel->GetCharged().IsSet())
            {
                Self->Charged = Domain->Charged = ResultModel->GetCharged();
            }
            Self->Output = Domain->Output = ResultModel->GetOutput();
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FInvokeScriptTask>> FNamespaceDomain::InvokeScript(
        Request::FInvokeScriptRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FInvokeScriptTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FDebugInvokeTask::FDebugInvokeTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FDebugInvokeRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FDebugInvokeTask::FDebugInvokeTask(
        const FDebugInvokeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FDebugInvokeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack);
        const auto Future = Self->Client->DebugInvoke(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetCode().IsSet())
            {
                Self->Code = Domain->Code = ResultModel->GetCode();
            }
            if (ResultModel->GetResult().IsSet())
            {
                Self->Result = Domain->Result = ResultModel->GetResult();
            }
            if (ResultModel->GetExecuteTime().IsSet())
            {
                Self->ExecuteTime = Domain->ExecuteTime = ResultModel->GetExecuteTime();
            }
            if (ResultModel->GetCharged().IsSet())
            {
                Self->Charged = Domain->Charged = ResultModel->GetCharged();
            }
            Self->Output = Domain->Output = ResultModel->GetOutput();
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDebugInvokeTask>> FNamespaceDomain::DebugInvoke(
        Request::FDebugInvokeRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDebugInvokeTask>>(this->AsShared(), Request);
    }

    Gs2::Script::Domain::Iterator::FDescribeScriptsIteratorPtr FNamespaceDomain::Scripts(
    ) const
    {
        return MakeShared<Gs2::Script::Domain::Iterator::FDescribeScriptsIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeScripts(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Script::Model::FScript::TypeName,
            Gs2::Script::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "Script"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeScripts(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Script::Model::FScript::TypeName,
            Gs2::Script::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "Script"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Script::Domain::Model::FScriptDomain> FNamespaceDomain::Script(
        const FString ScriptName
    )
    {
        return MakeShared<Gs2::Script::Domain::Model::FScriptDomain>(
            Gs2,
            Service,
            NamespaceName,
            ScriptName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ScriptName)
        );
    }

    FString FNamespaceDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FNamespaceDomain::CreateCacheKey(
        TOptional<FString> NamespaceName
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null");
    }

    FNamespaceDomain::FModelTask::FModelTask(
        const TSharedPtr<FNamespaceDomain> Self
    ): Self(Self)
    {

    }

    FNamespaceDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Script::Model::FNamespace>> Result
    )
    {
        const auto ParentKey = FString("script:Namespace");
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Script::Model::FNamespace> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Script::Model::FNamespace>(
            ParentKey,
            Gs2::Script::Domain::Model::FNamespaceDomain::CreateCacheKey(
                Self->NamespaceName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Script::Request::FGetNamespaceRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Script::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    Self->NamespaceName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Script::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "namespace")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Script::Model::FNamespace>(
                ParentKey,
                Gs2::Script::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    Self->NamespaceName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FModelTask>> FNamespaceDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNamespaceDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::Subscribe(
        TFunction<void(Gs2::Script::Model::FNamespacePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Script::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Script::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Script::Model::FNamespace>(obj));
            }
        );
    }

    void FNamespaceDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Script::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Script::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
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

