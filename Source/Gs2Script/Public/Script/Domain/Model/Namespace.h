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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Script/Gs2Script.h"
#include "Script/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Script/Domain/Iterator/DescribeScriptsIterator.h"

namespace Gs2::Script::Domain::Model
{
    class FNamespaceDomain;
    class FScriptDomain;

    class GS2SCRIPT_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Script::FGs2ScriptRestClientPtr Client;

        public:
        TOptional<FString> Status;
        TOptional<int32> Code;
        TOptional<FString> Result;
        TOptional<int32> ExecuteTime;
        TOptional<int32> Charged;
        TSharedPtr<TArray<FString>> Output;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetStatus() const
        {
            return Status;
        }
        TOptional<int32> GetCode() const
        {
            return Code;
        }
        TOptional<FString> GetResult() const
        {
            return Result;
        }
        TOptional<int32> GetExecuteTime() const
        {
            return ExecuteTime;
        }
        TOptional<int32> GetCharged() const
        {
            return Charged;
        }
        TSharedPtr<TArray<FString>> GetOutput() const
        {
            return Output;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FNamespaceDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2SCRIPT_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Script::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FGetStatusTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceStatusRequestPtr Request;
        public:
            explicit FGetStatusTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FGetNamespaceStatusRequestPtr Request
            );

            FGetStatusTask(
                const FGetStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2SCRIPT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Script::Model::FNamespace>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FGetNamespaceRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Script::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2SCRIPT_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Script::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FUpdateNamespaceRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FUpdateNamespaceRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2SCRIPT_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Script::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeleteNamespaceRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FDeleteNamespaceRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2SCRIPT_API FCreateScriptTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Script::Domain::Model::FScriptDomain>,
            public TSharedFromThis<FCreateScriptTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateScriptRequestPtr Request;
        public:
            explicit FCreateScriptTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FCreateScriptRequestPtr Request
            );

            FCreateScriptTask(
                const FCreateScriptTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FScriptDomain>> Result
            ) override;
        };
        friend FCreateScriptTask;

        TSharedPtr<FAsyncTask<FCreateScriptTask>> CreateScript(
            Request::FCreateScriptRequestPtr Request
        );

        class GS2SCRIPT_API FCreateScriptFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Script::Domain::Model::FScriptDomain>,
            public TSharedFromThis<FCreateScriptFromGitHubTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateScriptFromGitHubRequestPtr Request;
        public:
            explicit FCreateScriptFromGitHubTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FCreateScriptFromGitHubRequestPtr Request
            );

            FCreateScriptFromGitHubTask(
                const FCreateScriptFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FScriptDomain>> Result
            ) override;
        };
        friend FCreateScriptFromGitHubTask;

        TSharedPtr<FAsyncTask<FCreateScriptFromGitHubTask>> CreateScriptFromGitHub(
            Request::FCreateScriptFromGitHubRequestPtr Request
        );

        class GS2SCRIPT_API FInvokeScriptTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Script::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FInvokeScriptTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FInvokeScriptRequestPtr Request;
        public:
            explicit FInvokeScriptTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FInvokeScriptRequestPtr Request
            );

            FInvokeScriptTask(
                const FInvokeScriptTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FInvokeScriptTask;

        TSharedPtr<FAsyncTask<FInvokeScriptTask>> InvokeScript(
            Request::FInvokeScriptRequestPtr Request
        );

        class GS2SCRIPT_API FDebugInvokeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Script::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FDebugInvokeTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDebugInvokeRequestPtr Request;
        public:
            explicit FDebugInvokeTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FDebugInvokeRequestPtr Request
            );

            FDebugInvokeTask(
                const FDebugInvokeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDebugInvokeTask;

        TSharedPtr<FAsyncTask<FDebugInvokeTask>> DebugInvoke(
            Request::FDebugInvokeRequestPtr Request
        );

        Gs2::Script::Domain::Iterator::FDescribeScriptsIteratorPtr Scripts(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeScripts(
            TFunction<void()> Callback
        );

        void UnsubscribeScripts(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Script::Domain::Model::FScriptDomain> Script(
            const FString ScriptName
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2SCRIPT_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Script::Model::FNamespace>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FNamespaceDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Script::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Script::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
